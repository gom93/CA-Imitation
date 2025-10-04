#pragma once

#include <string>

class Utils
{
public:
	static std::string		ToString(const std::wstring& s);
	static std::wstring		ToWString(const std::string& s);
	static std::string		GetFileNameFromPath(const std::string& p);
	static std::wstring		GetFileNameFromPath(const std::wstring& p);
	static std::string		GetFileNameWidhoutExtension(const std::string& p);
	static std::wstring		GetFileNameWidhoutExtension(const std::wstring& p);
	
	static bool FileExists(const std::string& p);
};

