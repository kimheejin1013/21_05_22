#pragma once

#include "Enemy.h"


class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

private:
	std::vector<Enemy*> m_Enemys;


public:
	void Update();
	void Render();


};

