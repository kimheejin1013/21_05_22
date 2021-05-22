#pragma once
#include <sys/stat.h>	//	파일 데이터 영역 라이브러리
#include <fstream>		//	파일 스트림	(C++)

class FileUtility
{
public:
	//	파일 있냐 없냐?
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
