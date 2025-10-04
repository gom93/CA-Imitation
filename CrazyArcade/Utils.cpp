#include "pch.h"
#include "Utils.h"

#include <filesystem>
namespace fs = std::filesystem;

std::string Utils::ToString(const std::wstring& s)
{
	if (s.empty())
	{
		return "";
	}

	int needSize = WideCharToMultiByte(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0, nullptr, nullptr);

	std::string out(needSize, 0);
	WideCharToMultiByte(CP_UTF8, 0, s.c_str(), (int)s.size(), &out[0], needSize, nullptr, nullptr);

	return out;
}

std::wstring Utils::ToWString(const std::string& s)
{
	if (s.empty())
	{
		return L"";
	}

	int needSize = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), nullptr, 0);

	std::wstring out(needSize, 0);
	MultiByteToWideChar(CP_UTF8, 0, s.c_str(), (int)s.size(), &out[0], needSize);

	return out;
}

std::string Utils::GetFileNameFromPath(const std::string& p)
{
	int pos = (int)p.find_last_of("/\\");
	if (pos == std::string::npos)
	{
		return p;
	}
	return p.substr(pos + 1);
}

std::wstring Utils::GetFileNameFromPath(const std::wstring& p)
{
	int pos = (int)p.find_last_of(L"/\\");
	if (pos == std::wstring::npos)
	{
		return p;
	}
	return p.substr(pos + 1);
}

std::string Utils::GetFileNameWidhoutExtension(const std::string& p)
{
	std::string fileName = GetFileNameFromPath(p);
	int pos = (int)fileName.find_last_of('.');
	if (pos == std::string::npos)
	{
		return fileName;
	}
	return fileName.substr(0, pos);
}

std::wstring Utils::GetFileNameWidhoutExtension(const std::wstring& p)
{
	std::wstring fileName = GetFileNameFromPath(p);
	int pos = (int)fileName.find_last_of(L'.');
	if (pos == std::wstring::npos)
	{
		return fileName;
	}
	return fileName.substr(0, pos);
}

bool Utils::FileExists(const std::string& p)
{
	return fs::exists(p) && fs::is_regular_file(p);
}
