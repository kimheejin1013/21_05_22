#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	m_Rect = D2D1::RectF(_Application->Width / 2.0f - 10.0f,
		_Application->Height - 70.0f,
		_Application->Width / 2.0f + 10.0f,
		_Application->Height);
}

Player::~Player()
{
}

void Player::Update()
{
	if (_KeyCode->GetKey('A')) {
		m_Rect.left -= 5.0f;
		m_Rect.right -= 5.0f;
	}
	else if (_KeyCode->GetKey('D')) {
		m_Rect.left += 5.0f;
		m_Rect.right += 5.0f;
	}
}

void Player::Render()
{
	_RenderTarget->DrawRectangle(m_Rect, _Renderer->GetBrush());
}
