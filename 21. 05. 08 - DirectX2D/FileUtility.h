#pragma once
#include <sys/stat.h>	//	���� ������ ���� ���̺귯��
#include <fstream>		//	���� ��Ʈ��	(C++)

class FileUtility
{
public:
	//	���� �ֳ� ����?
	static inline bool Exists(const std::wstring& path)
	{
		std::string str = StringUtility::ConvertString(path);
		return Exists(str);
	}

	static inline bool Exists(const std::string& path)
	{
		struct stat buffer;
		return (stat(path.c_str(), &buffer) == 0);
	}

	static inline std::wstring GetResourcePath(std::wstring path)
	{
		std::wstring directory = L"../_Resources/";
		return directory.append(path);
	}

};
