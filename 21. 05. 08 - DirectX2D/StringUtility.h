#pragma once

class StringUtility
{
public:
	static inline std::string ConvertString(const std::wstring& wstr)
	{
		std::string str;
		return str.assign(wstr.begin(), wstr.end());
	}

	static inline std::wstring ConvertString(const std::string& str)
	{
		std::wstring wstr;
		return wstr.assign(str.begin(), str.end());
	}
};
