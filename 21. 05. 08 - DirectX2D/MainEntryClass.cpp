#include "stdafx.h"
#include "MainEntryClass.h"

//	�� cpp �� ������ �д� ���

//	�� ������ ���⿡�ٰ� �������ּ���!
MainEntryClass::MainEntryClass()
{
	m_Scenes.push_back(new BaseScene());
}

MainEntryClass::~MainEntryClass()
{
	for (auto i : m_Scenes)
		SAFE_DELETE(i);

	m_Scenes.clear();
	//	���� ���Ϳ� clear ȣ�� �� ���� ���Ҵ� ���� ������
	//	capacity (����) �� ���� �ʴ´�
	//	���� ó���� ���� 10���� �ְ�, clear ȣ�� �� �� ���� 10ĭ�� ��������
	//	�׷��� �� �� �������� �����ϱ� ���� ���� ������ �̿��Ͽ� �����Ѵ�
	std::vector<IScene*>().swap(m_Scenes);

	InputManager::Get()->Release();
}

HRESULT MainEntryClass::Start()
{
	//	���� 1
	//	HRESULT �˾ƿ���

	try
	{
		for (auto i : m_Scenes)
			i->Start();
	}
	catch (HRESULT h) // std::exception
	{
		HResult(h);
		return h;
	}

	return S_OK;
}

void MainEntryClass::Update()
{
	for (auto i : m_Scenes)
		i->Update();
}

void MainEntryClass::Render()
{
	for (auto i : m_Scenes)
		i->Render();
}
