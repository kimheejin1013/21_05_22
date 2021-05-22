#include "stdafx.h"

GraphicRenderer::GraphicRenderer()
	: m_D2DFactory(nullptr), m_DWriteFactory(nullptr), m_WICFactory(nullptr), m_RenderTarget(nullptr)
	, m_AntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE)
	, m_SolidBrush(nullptr), m_DefaultFont(nullptr)
{
}

GraphicRenderer::~GraphicRenderer()
{
	SAFE_RELEASE(m_DefaultFont);
	SAFE_RELEASE(m_SolidBrush);

	SAFE_RELEASE(m_RenderTarget);
	SAFE_RELEASE(m_WICFactory);
	SAFE_RELEASE(m_DWriteFactory);
	SAFE_RELEASE(m_D2DFactory);

	//	COM 객체 (Component Object Model)
	CoUninitialize();
}

HRESULT GraphicRenderer::OnCreateDeviceResource(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	//	클라이언트 렉트 계산한다
	D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);
	HResult(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_D2DFactory));

	//	그래픽 카드를 사용하기 위해 D2D 팩토리를 불러온다 (팩토리 메서드 패턴)
	HResult(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_DWriteFactory),
			reinterpret_cast<IUnknown**>(&m_DWriteFactory))
	);

	//	COM 객체 생성
	//	팩토리 사용 시 요 COM 객체가 필요함!
	CoInitialize(nullptr);
	HResult(
		CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC,
			IID_PPV_ARGS(&m_WICFactory)));

	//	위에 클라이언트 위치를 계산한 값과
	//	내가 현재 가지고 있는 hWnd(핸들) 에다가 그려달라 말해준다
	HResult(
		m_D2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&m_RenderTarget));

	m_RenderTarget->SetAntialiasMode(m_AntialiasMode);

	//	브러쉬 초기화
	if (FAILED(m_RenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black), &m_SolidBrush
	))) return E_FAIL;

	//	폰트 초기화
	m_DWriteFactory->CreateTextFormat(
		L"휴먼굴림체",				//	폰트 체
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,	//	폰트 중량
		DWRITE_FONT_STYLE_NORMAL,	//	폰트 스타일
		DWRITE_FONT_STRETCH_NORMAL,	//	폰트 스케일 타입
		14.0f, L"",
		&m_DefaultFont);

	return S_OK;
}

void GraphicRenderer::OnResize(UINT width, UINT height)
{
	if (m_RenderTarget) m_RenderTarget->Resize(D2D1::SizeU(width, height));
}

void GraphicRenderer::BeginDraw()
{
	m_RenderTarget->BeginDraw();
	m_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::DarkGray));

	m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void GraphicRenderer::EndDraw()
{
	m_RenderTarget->EndDraw();
}

void GraphicRenderer::DrawFontText(D2D1_RECT_F rect, std::wstring text)
{
	m_RenderTarget->DrawTextW(
		text.c_str(),
		static_cast<UINT32>(text.size()),
		m_DefaultFont,
		rect,
		m_SolidBrush);
}

//	결과값을 두 개 이상 주고싶을 때
//	함수는 리턴형 단 한개만 반환하기 때문에 어렵다!
//	그래서 Out 형 메소드 (pointer) 를 사용한다!
//	_Out_ 이 형식은 C 언어 형식, C++ OUT
HRESULT GraphicRenderer::CreateBitmap(
	_Out_ ID2D1Bitmap ** ppBitmap,
	_In_ std::wstring filePath,
	_In_ float width,
	_In_ float height,
	_In_ float alphaThresholdPercent,
	_In_ WICBitmapDitherType dither,
	_In_ WICBitmapPaletteType palette)
{
	//	GDI (맨 처음에 했던 winAPI) - CPU 에서 처리했던거
	//	구식 그래픽 라이브러리 - BMP 만 로드할 수 있었다 ..
	
	//	허나 D2D 를 사용함으로써 그래픽 카드를 사용하고
	//	추가 라이브러리를 통해 JPG, JPEG 는 물론 PNG 도 로드할 수 있도록 한다!
	//	BMP - 무손실 압축 이미지
	//	JPG - 손실 압축 이미지
	//	PNG - 무손실 압축 이미지

	IWICFormatConverter* pWICConverter = nullptr;
	IWICBitmapFrameDecode* pWICFrameDecode = nullptr;
	IWICBitmapDecoder* pWICDecoder = nullptr;
	
	try
	{
		std::string convertStr = StringUtility::ConvertString(filePath);
		if (!FileUtility::Exists(convertStr))
		{
			HThrow((HRESULT)0x80070002);
		}

		HThrow(m_WICFactory->CreateDecoderFromFilename(
			filePath.c_str(),	//	LPC (long point const) 이거 만나면 스트링 또는 와이드 스트링 .c_str()
			nullptr,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&pWICDecoder));

		HThrow(m_WICFactory->CreateFormatConverter(&pWICConverter));
		HThrow(pWICDecoder->GetFrame(0, &pWICFrameDecode));
		HThrow(pWICConverter->Initialize(
			pWICFrameDecode,
			GUID_WICPixelFormat32bppPRGBA,
			dither,
			nullptr,
			alphaThresholdPercent,
			palette
		));

		HThrow(m_RenderTarget->CreateBitmapFromWicBitmap(
			pWICConverter,
			nullptr,
			ppBitmap
		));
	}
	catch (const HRESULT hr)
	{
		SAFE_RELEASE(pWICConverter);
		SAFE_RELEASE(pWICDecoder);
		SAFE_RELEASE(pWICFrameDecode);

		return hr;
	}

	SAFE_RELEASE(pWICConverter);
	SAFE_RELEASE(pWICDecoder);
	SAFE_RELEASE(pWICFrameDecode);

	return S_OK;
}
