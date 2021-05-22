#pragma once

class Player
{
public:
	Player();
	~Player();

private:
	D2D1_RECT_F m_Rect;

public:
	void Update();
	void Render();

public:
	D2D1_RECT_F GetRect() { return m_Rect; }
};

