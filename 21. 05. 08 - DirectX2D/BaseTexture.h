#pragma once

class BaseTexture
{
public:
	BaseTexture(std::wstring fileName);
	BaseTexture(std::wstring fileName, UINT frameX, UINT frameY);
	~BaseTexture();

public:
	D2D1_SIZE_F GetSize() const
	{
		if (m_FrameSize.width != 0.0f) return m_FrameSize;
		return m_Bitmap->GetSize();
	}

private:
	ID2D1Bitmap* m_Bitmap;

	D2D1_SIZE_F m_FrameSize;
	UINT m_MaxFrameX;
	UINT m_MaxFrameY;

public:
	void Draw(float x, float y, float opacity = 1.0f);
	void Draw(float x, float y, float scaleX, float scaleY, float opacity = 1.0f);
	void Draw(float x, float y, float scaleX, float scaleY, bool isReverse, float opacity = 1.0f);
	void Draw(float x, float y, float scaleX, float scaleY, bool isReverse, float degree, float opacity = 1.0f);
	void DrawCrop(float x, float y, float startX, float startY, float endX, float endY, float scaleX, float scaleY, float opacity = 1.0f);
	void DrawFrame(float x, float y, UINT fx, UINT fy, float opacity = 1.0f);
	void DrawFrame(float x, float y, UINT fx, UINT fy, float scaleX, float scaleY, bool isReverse, float opacity = 1.0f);
	void DrawFrame(float x, float y, UINT fx, UINT fy, float scaleX, float scaleY, bool isReverse, float degree, float opacity = 1.0f);
};

