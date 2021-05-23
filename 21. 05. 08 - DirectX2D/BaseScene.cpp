#include "stdafx.h"
#include "BaseScene.h"

BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{
	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_Enemys);
}

HRESULT BaseScene::Start()
{
	m_Player = new Player();
	m_Enemys = new EnemyManager();

	isGameOver = false;

	return S_OK;
}

void BaseScene::Update()
{
	if (isGameOver==false) {

	m_Player->Update();
	m_Enemys->Update();
	}

	if (m_Enemys->IntersectRect(m_Player->GetRect()))
		isGameOver = true;


}

void BaseScene::Render()
{
	m_Player->Render();
	m_Enemys->Render();

}
