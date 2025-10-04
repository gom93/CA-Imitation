#pragma once

struct CLICK_EVENT
{
	ENTITY_INDEX id;
	bool isRight;
};

enum class CHARACTER_SELECT_TYPE
{
	Bazzi,
	Dizni,
	Random,
};

class Entity;

class MessageQueue
{
public:
	static int		StringToEnum(const std::string& str);

	static void		Run(const std::list<Entity*>& entities, OUT SCENE_TYPE& type);

	static void		AddEvent(CLICK_EVENT evt);

private:
	static void		MessageLoop(const CLICK_EVENT evt, const std::list<Entity*>& entities, OUT SCENE_TYPE& type);
	static void		OnPickCharacter(const std::list<Entity*>& entities, bool isRight, CHARACTER_SELECT_TYPE type);

private:
	static std::unordered_map<std::string, int> s_strToEnumTable;

	static std::queue<CLICK_EVENT>				s_eventQueue;

public:
	static SELECT_DATA							SelectData;
};

