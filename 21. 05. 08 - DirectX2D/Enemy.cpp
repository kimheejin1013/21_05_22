#include "stdafx.h"
#include "Enemy.h"

#include <time.h>

Enemy::Enemy()
{
	srand(time(NULL));

	float size = rand() % 70 + 30;
	float halfSize = size / 2.0f;

		m_Rect = D2D1::RectF(100, 100, 200, 200); //¿©±ä¿ìÂ§´ô...
	
	
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	float size = rand() % 70 + 30;
	float halfSize = size / 2.0f;

	float leftSize = rand() % _Application->Width;

	if (_Application->Height < m_Rect.top) {

	m_Rect.top = - size + halfSize;
	m_Rect.bottom = 0.0f;


	m_Rect.left = leftSize;
	m_Rect.right = leftSize + halfSize;
	//m_Rect.left = rand() % _Application->Width;			
	//m_Rect.right = m_Rect.left + 100.0f;
	
	if (m_Rect.right > _Application->Width) {
		m_Rect.left = _Application->Width - (size - halfSize);
		m_Rect.right = _Application->Width;
	}}
	
	float Speed = rand() % 15 + 5.0f;

	m_Rect.top += Speed;
	m_Rect.bottom += Speed;
}

void Enemy::Render()
{
	_RenderTarget->DrawRectangle(m_Rect, _Renderer->GetBrush());

}
