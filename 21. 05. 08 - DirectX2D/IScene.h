#pragma once
#include "stdafx.h"

//	�ȿ� ���� ���� �Ұ���
//	���� �Լ� ���� ���� �Ұ���
//	���� �����⸸ ���� (��(form)�� ����)
__interface IScene
{
	HRESULT Start();
	void Update();
	void Render();
};
