#pragma once
#include "BaseScene.h"

__interface IScene;
class MainEntryClass
{
public:
	MainEntryClass();
	~MainEntryClass();

private:
	std::vector<IScene*> m_Scenes;

public:
	HRESULT Start();
	void Update();
	void Render();

};

