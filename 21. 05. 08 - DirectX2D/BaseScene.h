#pragma once
#include "Player.h"
#include "EnemyManager.h"

class BaseScene : public IScene
{
public:
	BaseScene();
	~BaseScene();

private:
	Player* m_Player;
	Enemy* m_Enemy;

	bool isGameOver;

public:
	// IScene��(��) ���� ��ӵ�
	virtual HRESULT Start() override;
	virtual void Update() override;
	virtual void Render() override;
};

