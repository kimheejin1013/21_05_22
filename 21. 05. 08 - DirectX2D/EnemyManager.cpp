#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	for (int i=0; i<20; ++i)
	{
		Enemy* e = new Enemy;
		m_Enemys.push_back(e); 
	}
}

EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update()
{
	for (auto p : m_Enemys)
		p->Update();
}

void EnemyManager::Render()
{
	for (auto p : m_Enemys)
		p->Render();
}

bool EnemyManager::IntersectRect(D2D1_RECT_F playerRc)
{
	for (auto p : m_Enemys)
	{
		if (p->IntersectRect(playerRc))
			return true;
	}

	return false;
}
