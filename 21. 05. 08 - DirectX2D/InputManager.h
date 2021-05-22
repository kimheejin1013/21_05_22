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
	bool GetKeyDown(int keyCode);	//	키를 눌렀다면 발동			-	한 번만
	bool GetKey(int keyCode);		//	키를 누르고 있다면 발동		-	여러번
	bool GetKeyUp(int keyCode);		//	키를 눌렀다가 뗏을 때 발동	-	한 번만
	bool ToggleKey(int keyCode);	//	토글키가 켜져 있을 때 발동	-	여러번
};

#define _KeyCode InputManager::Get()
