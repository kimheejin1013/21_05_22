#include "stdafx.h"
#include "Enemy.h"

#include <time.h>

Enemy::Enemy()
{
	srand(time(NULL));


	m_Rect = D2D1::RectF(100.0f, 100.0f, 200.0f, 200.0f);

	
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{

	if (_Application->Height < m_Rect.top) {

	m_Rect.top = -100.0f;
	m_Rect.bottom = 0.0f;


	m_Rect.left = rand() % _Application->Width;			
	m_Rect.right = m_Rect.left + 100.0f;
	
	if (m_Rect.right > _Application->Width) {
		m_Rect.left = _Application->Width - 100.0f;
		m_Rect.right = _Application->Width;
	}}
	
	m_Rect.top += 10.0f;
	m_Rect.bottom += 10.0f;
}

void Enemy::Render()
{
	_RenderTarget->DrawRectangle(m_Rect, _Renderer->GetBrush());

}
