#pragma once
#include "BaseSingleton.h"

class InputManager : public BaseSingleton<InputManager>
{
public:
	InputManager();

private:
	//	usgined char
	byte m_KeyDown[256];
	byte m_PrevKey[256];

public:
	bool GetKeyDown(int keyCode);	//	Ű�� �����ٸ� �ߵ�			-	�� ����
	bool GetKey(int keyCode);		//	Ű�� ������ �ִٸ� �ߵ�		-	������
	bool GetKeyUp(int keyCode);		//	Ű�� �����ٰ� ���� �� �ߵ�	-	�� ����
	bool ToggleKey(int keyCode);	//	���Ű�� ���� ���� �� �ߵ�	-	������
};

#define _KeyCode InputManager::Get()
