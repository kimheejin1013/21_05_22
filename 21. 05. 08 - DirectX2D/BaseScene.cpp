#include "stdafx.h"
#include "BaseScene.h"

BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{
	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_Enemy);
}

HRESULT BaseScene::Start()
{
	m_Player = new Player();
	m_Enemy = new Enemy();

	isGameOver = false;

	return S_OK;
}

void BaseScene::Update()
{
	if (isGameOver==false) {

	m_Player->Update();
	m_Enemy->Update();

	}

	if (m_Enemy->IntersectRect(m_Player->GetRect()))
	{
		isGameOver = true;
	}

}

void BaseScene::Render()
{
	m_Player->Render();
	m_Enemy->Render();

	
}
