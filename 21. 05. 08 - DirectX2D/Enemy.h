#pragma once

class Enemy
{
	struct EnemyRect
	{
		D2D1_RECT_F Rect;
		
	
		D2D1_RECT_F GetRect(float x, float y, float width, float height)
		{
			return D2D1::RectF(x, y, x + width, y + height);
		}
	};

public:
	Enemy();
	~Enemy();

private:
	
	D2D1_RECT_F m_Rect;
	

public:
	void Update();
	void Render();

	bool IntersectRect(D2D1_RECT_F playerRc)
	{
	
		if (m_Rect.left <= playerRc.right &&
			m_Rect.right >= playerRc.left &&
			m_Rect.top <= playerRc.bottom &&
			m_Rect.bottom >= playerRc.top)
			return true;
		
		return false;
	}
	
};

