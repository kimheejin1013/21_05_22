#include "stdafx.h"
#include "BaseTexture.h"

BaseTexture::BaseTexture(std::wstring fileName)
	: m_Bitmap(nullptr)
{
	_Renderer->CreateBitmap(&m_Bitmap, fileName);
}

BaseTexture::BaseTexture(std::wstring fileName, UINT frameX, UINT frameY)
	: m_Bitmap(nullptr)
{
	_Renderer->CreateBitmap(&m_Bitmap, fileName);

	m_MaxFrameX = frameX;
	m_MaxFrameY = frameY;

	m_FrameSize = { GetSize().width / frameX, GetSize().height / frameY };
}

BaseTexture::~BaseTexture()
{
	SAFE_RELEASE(m_Bitmap);
}

void BaseTexture::Draw(float x, float y, float opacity)
{
	if (!m_Bitmap) return;

	//	화면에서 어떻게 그려줄 건지 ?
	D2D1_RECT_F location = D2D1::RectF(
		x,
		y,
		x + GetSize().width,
		y + GetSize().height
	);

	//	실제 이미지 에서 어디서부터 어디까지 그려줄 것인지 ?
	D2D1_RECT_F uvSize = D2D1::RectF(
		0.0f,
		0.0f,
		GetSize().width,
		GetSize().height
	);

	_RenderTarget->DrawBitmap(
		m_Bitmap,
		location,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		uvSize
	);
}

void BaseTexture::Draw(float x, float y, float scaleX, float scaleY, float opacity)
{
	if (!m_Bitmap) return;

	//	화면에서 어떻게 그려줄 건지 ?
	D2D1_RECT_F location = D2D1::RectF(
		x,
		y,
		x + scaleX,
		y + scaleY
	);

	//	실제 이미지 에서 어디서부터 어디까지 그려줄 것인지 ?
	D2D1_RECT_F uvSize = D2D1::RectF(
		0.0f,
		0.0f,
		GetSize().width,
		GetSize().height
	);

	_RenderTarget->DrawBitmap(
		m_Bitmap,
		location,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		uvSize
	);
}

void BaseTexture::Draw(float x, float y, float scaleX, float scaleY, bool isReverse, float opacity)
{
	if (!m_Bitmap) return;
	if (scaleX == 0.0f || scaleY == 0.0f)
	{
		scaleX = GetSize().width;
		scaleY = GetSize().height;
	}

	D2D1_RECT_F location = D2D1::RectF(
		x,
		y,
		x + scaleX,
		y + scaleY
	);

	D2D1_RECT_F uvSize = D2D1::RectF(
		0.0f,
		0.0f,
		GetSize().width,
		GetSize().height
	);

	if (isReverse) {
		D2D_POINT_2F pivot = { x + scaleX / 2.0f, y / scaleY / 2.0f };
		D2D1::Matrix3x2F matrix = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, pivot);

		_RenderTarget->SetTransform(matrix);
	}
	else _RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_RenderTarget->DrawBitmap(
		m_Bitmap,
		location,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		uvSize
	);
}

void BaseTexture::Draw(float x, float y, float scaleX, float scaleY, bool isReverse, float degree, float opacity)
{
}

void BaseTexture::DrawCrop(float x, float y, float startX, float startY, float endX, float endY, float scaleX, float scaleY, float opacity)
{
	if (!m_Bitmap) return;

	D2D1_RECT_F location = D2D1::RectF(
		x, y,
		x + scaleX,
		y + scaleY
	);

	D2D1_RECT_F uvSize = D2D1::RectF(
		startX,
		startY,
		endX,
		endY
	);

	_RenderTarget->DrawBitmap(
		m_Bitmap,
		location,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		uvSize
	);

}

void BaseTexture::DrawFrame(float x, float y, UINT fx, UINT fy, float opacity)
{
	if (!m_Bitmap) return;

	D2D1_RECT_F location = D2D1::RectF(
		x,
		y,
		x + m_FrameSize.width,
		y + m_FrameSize.height
	);

	D2D1_RECT_F uvSize = D2D1::RectF(
		fx * m_FrameSize.width,
		fy * m_FrameSize.height,
		(fx + 1) * m_FrameSize.width,
		(fy + 1) * m_FrameSize.height
	);

	_RenderTarget->DrawBitmap(
		m_Bitmap,
		location,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		uvSize
	);
}

void BaseTexture::DrawFrame(float x, float y, UINT fx, UINT fy, float scaleX, float scaleY, bool isReverse, float opacity)
{
	if (!m_Bitmap) return;
	if (scaleX == 0.0f || scaleY == 0.0f)
	{
		scaleX = m_FrameSize.width;
		scaleY = m_FrameSize.height;
	}

	D2D1_RECT_F location = D2D1::RectF(
		x,
		y,
		x + scaleX,
		y + scaleY
	);

	D2D1_RECT_F uvSize = D2D1::RectF(
		fx * m_FrameSize.width,
		fy * m_FrameSize.height,
		(fx + 1) * m_FrameSize.width,
		(fy + 1) * m_FrameSize.height
	);

	if (isReverse)
	{
		D2D_POINT_2F pivot = { x + scaleX / 2.0f, y + scaleY / 2.0f };
		D2D1::Matrix3x2F matrix = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, pivot);

		_RenderTarget->SetTransform(matrix);
	}
	else _RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	_RenderTarget->DrawBitmap(
		m_Bitmap,
		location,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		uvSize
	);
}

void BaseTexture::DrawFrame(float x, float y, UINT fx, UINT fy, float scaleX, float scaleY, bool isReverse, float degree, float opacity)
{
	if (!m_Bitmap) return;
	if (scaleX == 0.0f || scaleY == 0.0f)
	{
		scaleX = m_FrameSize.width;
		scaleY = m_FrameSize.height;
	}

	D2D1_RECT_F location = D2D1::RectF(
		x,
		y,
		x + scaleX,
		y + scaleY
	);

	D2D1_RECT_F uvSize = D2D1::RectF(
		fx * m_FrameSize.width,
		fy * m_FrameSize.height,
		(fx + 1) * m_FrameSize.width,
		(fy + 1) * m_FrameSize.height
	);

	D2D_POINT_2F pivot = { x + scaleX / 2.0f, y + scaleY / 2.0f };
	if (isReverse)
	{
		D2D1::Matrix3x2F matrix =
			D2D1::Matrix3x2F::Scale(-1.0f, 1.0f, pivot) *
			D2D1::Matrix3x2F::Rotation(degree, pivot);

		_RenderTarget->SetTransform(matrix);
	}
	else _RenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(degree, pivot));

	_RenderTarget->DrawBitmap(
		m_Bitmap,
		location,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		uvSize
	);
}
