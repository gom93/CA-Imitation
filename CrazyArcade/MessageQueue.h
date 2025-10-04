#pragma once

class MessageQueue
{
public:
	static int StringToEnum(const std::string& str);

private:
	static std::unordered_map<std::string, int> s_strToEnumTable;
};

