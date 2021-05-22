#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager()
{
	//	숙제 2
	//	ZeroMemory, FillMemory 알아오기 (C++)
	ZeroMemory(m_KeyDown, sizeof m_KeyDown);
	ZeroMemory(m_PrevKey, sizeof m_PrevKey);
}

//	'A', 'W', 'S' -> char -> intiger
bool InputManager::GetKeyDown(int keyCode)
{
	if (GetAsyncKeyState(keyCode) & 0x8000)
	{
		if (!m_KeyDown[keyCode]) {
			m_KeyDown[keyCode] = 0x01;
			return true;
		}
	}
	else m_KeyDown[keyCode] = 0;

	return false;
}

bool InputManager::GetKey(int keyCode)
{
	if (GetAsyncKeyState(keyCode) & 0x8000) {
		m_PrevKey[keyCode] = 0x01;
		return true;
	}

	return false;
}

bool InputManager::GetKeyUp(int keyCode)
{
	if (!GetKey(keyCode)) {
		if (m_PrevKey[keyCode] == 0x01) {
			m_PrevKey[keyCode] = 0;
			return true;
		}
	}

	return false;
}

bool InputManager::ToggleKey(int keyCode)
{
	if (GetKeyState(keyCode) & 0x0001) return true;
	return false;
}
