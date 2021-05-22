#include "stdafx.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

BaseTexture * TextureManager::LoadTexture(std::string name, std::wstring filePath)
{
	BaseTexture* pTexture = nullptr;
	try
	{
		pTexture = new BaseTexture(filePath);

		if (pTexture == nullptr)
			HThrow(E_OUTOFMEMORY);

		//	map?
		//	key, value �� �Ѱ��� ������ �ִ� ����
		//	1. key �� ���� �ߺ��� �� ����!
		//	-> "AA" ��� �༮�� �ְ� �� ������ �� "AA" ��� ��ü�� ���� ��� ����!
		//	2. map �ȿ��� value �� ã�� ���� key ���� ����Ѵ�
		//	3. std::vector, std::list �ʹ� �ٸ��� ��ȯ�ؼ� ã�� ���� �ƴ�
		//	'����� Ʈ��' ��� �˰����� �̿��Ͽ� ã�´�
		//	V -> Ʈ�� ���� ? (����, ����, ����)

		//	make_pair ? std::map �ȿ��� ������ �� �� ���� ������
		//	���� �� ������ �༮�� make_pair ��� �Լ��� ����Ѵ�
		m_Textures.insert(std::make_pair(name, pTexture));
	}
	catch (const HRESULT hr)
	{
		//	.. ����ó��

		//	...
		SAFE_DELETE(pTexture);

		return nullptr;
	}
	
	return pTexture;
}

BaseTexture * TextureManager::LoadTexture(std::string name, std::wstring filePath, UINT frameX, UINT frameY)
{
	BaseTexture* pTexture = nullptr;
	try
	{
		pTexture = new BaseTexture(filePath, frameX, frameY);

		if (pTexture == nullptr)
			HThrow(E_OUTOFMEMORY);

		m_Textures.insert(std::make_pair(name, pTexture));
	}
	catch (const HRESULT hr)
	{
		SAFE_DELETE(pTexture);

		return nullptr;
	}

	return pTexture;
}

BaseTexture * TextureManager::Find(std::string name)
{
	if (m_Textures.empty()) return nullptr;
	
	/*std::map<std::string, BaseTexture*>::iterator iter = m_Textures.begin();
	for (iter; iter != m_Textures.end(); ++iter)
	{

	}*/

	for (auto i : m_Textures)
		if (i.first == name) return i.second;

	return nullptr;
}
