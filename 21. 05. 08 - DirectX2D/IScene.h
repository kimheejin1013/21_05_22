#pragma once
#include "stdafx.h"

//	안에 변수 구현 불가능
//	내부 함수 직접 구현 불가능
//	정말 껍데기만 제공 (폼(form)만 제공)
__interface IScene
{
	HRESULT Start();
	void Update();
	void Render();
};
