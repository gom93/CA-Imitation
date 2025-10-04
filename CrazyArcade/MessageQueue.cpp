#include "pch.h"
#include "MessageQueue.h"

std::unordered_map<std::string, int> MessageQueue::s_strToEnumTable =
{
	{ "Background"			, (int)ENTITY_INDEX::Background},
	{ "RedCharacter"		, (int)ENTITY_INDEX::RedCharacter },
	{ "BlueCharacter"		, (int)ENTITY_INDEX::BlueCharacter },
	{ "BazziPickImage"		, (int)ENTITY_INDEX::BazziPickImage },
	{ "DizniPickImage"		, (int)ENTITY_INDEX::DizniPickImage },
	{ "RandomPickImage"		, (int)ENTITY_INDEX::RandomPickImage },
	{ "Exit"				, (int)ENTITY_INDEX::Exit },
	{ "Map"					, (int)ENTITY_INDEX::Map },
	{ "MapPick"				, (int)ENTITY_INDEX::MapPick},
	{ "Start"				, (int)ENTITY_INDEX::Start },
	{ "Block"				, (int)ENTITY_INDEX::Block },
	{ "Wall"				, (int)ENTITY_INDEX::Wall },
	{ "WaterBallon"			, (int)ENTITY_INDEX::WaterBallon },
	{ "RedBazzi		"		, (int)ENTITY_INDEX::RedBazzi },
	{ "RedDizni		"		, (int)ENTITY_INDEX::RedDizni },
	{ "BlueBazzi"			, (int)ENTITY_INDEX::BlueBazzi},
	{ "BlueDizni"			, (int)ENTITY_INDEX::BlueDizni },
	{ "Trapped"				, (int)ENTITY_INDEX::Trapped },
	{ "Die"					, (int)ENTITY_INDEX::Die },
	{ "DrawUI"				, (int)ENTITY_INDEX::DrawUI },
	{ "LoseUI"				, (int)ENTITY_INDEX::LoseUI },
	{ "WinUI"				, (int)ENTITY_INDEX::WinUI },
	{ "BompUP"				, (int)ENTITY_INDEX::BompUP },
	{ "PowerUP"				, (int)ENTITY_INDEX::PowerUP },
	{ "SpeedUP"				, (int)ENTITY_INDEX::SpeedUP},
};

int MessageQueue::StringToEnum(const std::string& str)
{
	return s_strToEnumTable[str];
}
