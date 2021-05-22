#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>

#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "DWrite.lib")

class GraphicRenderer
{
public:
	//	Singleton	- 숙제 2
	//	디자인 패턴 - 싱글톤 찾아보기
	static GraphicRenderer* Get()
	{
		static GraphicRenderer instance;
		return &instance;
	}

	GraphicRenderer();
	GraphicRenderer(GraphicRenderer const&) = delete;
	~GraphicRenderer();
	void operator=(GraphicRenderer const&) = delete;

private:
	ID2D1Factory*			m_D2DFactory;
	IDWriteFactory*			m_DWriteFactory;
	IWICImagingFactory*		m_WICFactory;
	ID2D1HwndRenderTarget*	m_RenderTarget;
	D2D1_ANTIALIAS_MODE		m_AntialiasMode;

	//	Default Brush
	ID2D1SolidColorBrush*	m_SolidBrush;

	//	Defalt Font
	IDWriteTextFormat*		m_DefaultFont;

public:
	ID2D1HwndRenderTarget*	RenderTarget() const { return m_RenderTarget; }
	ID2D1SolidColorBrush*	GetBrush() const { return m_SolidBrush; }

public:
	HRESULT OnCreateDeviceResource(HWND hWnd);	//	초기화
	void OnResize(UINT width, UINT height);		//	윈도우 리사이즈 시 발동!

	void BeginDraw();
	void EndDraw();

	void DrawFontText(D2D1_RECT_F rect, std::wstring text);

	HRESULT CreateBitmap(
		_Out_ ID2D1Bitmap** ppBitmap,
		_In_  std::wstring filePath, _In_ float width = 1.0f, _In_ float height = 1.0f,
		_In_  float alphaThresholdPercent = 0.0f,
		_In_  WICBitmapDitherType dither = WICBitmapDitherTypeNone,
		_In_  WICBitmapPaletteType palette = WICBitmapPaletteTypeCustom);
};

#define _Renderer GraphicRenderer::Get()
#define _RenderTarget GraphicRenderer::Get()->RenderTarget()
