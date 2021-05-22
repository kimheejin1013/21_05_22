#pragma once
#include "BaseTexture.h"
#include <map>

class TextureManager : public BaseSingleton<TextureManager>
{
public:
	TextureManager();
	~TextureManager();

private:
	std::map<std::string, BaseTexture*> m_Textures;
	//	typedef = º°¸í
	//typedef std::map<std::string, BaseTexture*>::iterator iter;

public:
	BaseTexture* LoadTexture(std::string name, std::wstring filePath);
	BaseTexture* LoadTexture(std::string name, std::wstring filePath, UINT frameX, UINT frameY);
	BaseTexture* Find(std::string name);
};

#define _Texture TextureManager::Get()
