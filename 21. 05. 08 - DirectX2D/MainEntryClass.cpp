#include "stdafx.h"
#include "MainEntryClass.h"

//	이 cpp 안 에서만 읽는 헤더

//	씬 생성시 여기에다가 생성해주세요!
MainEntryClass::MainEntryClass()
{
	m_Scenes.push_back(new BaseScene());
}

MainEntryClass::~MainEntryClass()
{
	for (auto i : m_Scenes)
		SAFE_DELETE(i);

	m_Scenes.clear();
	//	실제 벡터에 clear 호출 시 안의 원소는 전부 삭제됨
	//	capacity (공간) 은 줄지 않는다
	//	내가 처음에 원소 10개를 넣고, clear 호출 시 빈 공간 10칸이 남아있음
	//	그래서 이 빈 공간마저 삭제하기 위해 밑의 스왑을 이용하여 삭제한다
	std::vector<IScene*>().swap(m_Scenes);

	InputManager::Get()->Release();
}

HRESULT MainEntryClass::Start()
{
	//	숙제 1
	//	HRESULT 알아오기

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
