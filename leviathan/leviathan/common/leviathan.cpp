#include "leviathan.h"
#include <Windows.h>

Leviathan::cLeviathan::cLeviathan()
{
}

Leviathan::cLeviathan::~cLeviathan()
{
}

bool Leviathan::cLeviathan::Booting(std::string config)
{
	if (!LoadConfig(config))
	{
		return false;
	}

	return true;
}

char* Leviathan::WideCharToMultiByte(const wchar_t* wstr)
{
	int wstr_len = (int)wcslen(wstr);
	int num_chars = ::WideCharToMultiByte(CP_UTF8, 0, wstr, wstr_len, NULL, 0, NULL, NULL);
	CHAR* strTo = (CHAR*)malloc((num_chars + 1) * sizeof(CHAR));

	if (strTo)
	{
		::WideCharToMultiByte(CP_UTF8, 0, wstr, wstr_len, strTo, num_chars, NULL, NULL);
		strTo[num_chars] = '\0';
	}

	return strTo;
}

std::string Leviathan::WideCharToMultiByte(const std::wstring& wstr)
{
	int num_chars = ::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
	std::string strTo;
	if (num_chars > 0)
	{
		strTo.resize(num_chars);
		::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), &strTo[0], num_chars, NULL, NULL);
	}
	return strTo;
}

wchar_t* Leviathan::MultiByteToWideChar(const char* str)
{
	int str_len = (int)strlen(str);
	int num_chars = ::MultiByteToWideChar(CP_UTF8, 0, str, str_len, NULL, 0);
	WCHAR* wstrTo = (WCHAR*)malloc((num_chars + 1) * sizeof(WCHAR));
	if (wstrTo)
	{
		::MultiByteToWideChar(CP_UTF8, 0, str, str_len, wstrTo, num_chars);
		wstrTo[num_chars] = L'\0';
	}
	return wstrTo;
}

std::wstring Leviathan::MultiByteToWideChar(const std::string& str)
{
	int num_chars = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring wstrTo;
	if (num_chars)
	{
		wstrTo.resize(num_chars);
		::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstrTo[0], num_chars);
	}
	return wstrTo;
}
