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

	//	COM ��ü (Component Object Model)
	CoUninitialize();
}

HRESULT GraphicRenderer::OnCreateDeviceResource(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);

	//	Ŭ���̾�Ʈ ��Ʈ ����Ѵ�
	D2D1_SIZE_U size = D2D1::SizeU(rect.right - rect.left, rect.bottom - rect.top);
	HResult(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &m_D2DFactory));

	//	�׷��� ī�带 ����ϱ� ���� D2D ���丮�� �ҷ��´� (���丮 �޼��� ����)
	HResult(
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_DWriteFactory),
			reinterpret_cast<IUnknown**>(&m_DWriteFactory))
	);

	//	COM ��ü ����
	//	���丮 ��� �� �� COM ��ü�� �ʿ���!
	CoInitialize(nullptr);
	HResult(
		CoCreateInstance(
			CLSID_WICImagingFactory,
			nullptr,
			CLSCTX_INPROC,
			IID_PPV_ARGS(&m_WICFactory)));

	//	���� Ŭ���̾�Ʈ ��ġ�� ����� ����
	//	���� ���� ������ �ִ� hWnd(�ڵ�) ���ٰ� �׷��޶� �����ش�
	HResult(
		m_D2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&m_RenderTarget));

	m_RenderTarget->SetAntialiasMode(m_AntialiasMode);

	//	�귯�� �ʱ�ȭ
	if (FAILED(m_RenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black), &m_SolidBrush
	))) return E_FAIL;

	//	��Ʈ �ʱ�ȭ
	m_DWriteFactory->CreateTextFormat(
		L"�޸ձ���ü",				//	��Ʈ ü
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,	//	��Ʈ �߷�
		DWRITE_FONT_STYLE_NORMAL,	//	��Ʈ ��Ÿ��
		DWRITE_FONT_STRETCH_NORMAL,	//	��Ʈ ������ Ÿ��
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

//	������� �� �� �̻� �ְ���� ��
//	�Լ��� ������ �� �Ѱ��� ��ȯ�ϱ� ������ ��ƴ�!
//	�׷��� Out �� �޼ҵ� (pointer) �� ����Ѵ�!
//	_Out_ �� ������ C ��� ����, C++ OUT
HRESULT GraphicRenderer::CreateBitmap(
	_Out_ ID2D1Bitmap ** ppBitmap,
	_In_ std::wstring filePath,
	_In_ float width,
	_In_ float height,
	_In_ float alphaThresholdPercent,
	_In_ WICBitmapDitherType dither,
	_In_ WICBitmapPaletteType palette)
{
	//	GDI (�� ó���� �ߴ� winAPI) - CPU ���� ó���ߴ���
	//	���� �׷��� ���̺귯�� - BMP �� �ε��� �� �־��� ..
	
	//	�㳪 D2D �� ��������ν� �׷��� ī�带 ����ϰ�
	//	�߰� ���̺귯���� ���� JPG, JPEG �� ���� PNG �� �ε��� �� �ֵ��� �Ѵ�!
	//	BMP - ���ս� ���� �̹���
	//	JPG - �ս� ���� �̹���
	//	PNG - ���ս� ���� �̹���

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
			filePath.c_str(),	//	LPC (long point const) �̰� ������ ��Ʈ�� �Ǵ� ���̵� ��Ʈ�� .c_str()
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
