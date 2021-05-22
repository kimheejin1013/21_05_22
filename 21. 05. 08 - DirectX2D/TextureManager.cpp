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
		//	key, value 각 한개씩 가지고 있는 구조
		//	1. key 는 절대 중복될 수 없다!
		//	-> "AA" 라는 녀석을 넣고 난 다음에 또 "AA" 라는 객체를 넣을 경우 에러!
		//	2. map 안에서 value 를 찾을 때는 key 값을 사용한다
		//	3. std::vector, std::list 와는 다르게 순환해서 찾는 것이 아닌
		//	'레드블랙 트리' 라는 알고리즘을 이용하여 찾는다
		//	V -> 트리 구조 ? (전위, 중위, 후위)

		//	make_pair ? std::map 안에는 데이터 두 개 들어가기 때문에
		//	넣을 때 도와줄 녀석인 make_pair 라는 함수를 사용한다
		m_Textures.insert(std::make_pair(name, pTexture));
	}
	catch (const HRESULT hr)
	{
		//	.. 예외처리

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
