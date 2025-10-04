#include "pch.h"
#include "MessageQueue.h"
#include "DynamicEntity.h"

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

std::queue<CLICK_EVENT> MessageQueue::s_eventQueue;
SELECT_DATA MessageQueue::SelectData = {};

int MessageQueue::StringToEnum(const std::string& str)
{
	return s_strToEnumTable[str];
}

void MessageQueue::AddEvent(CLICK_EVENT evt)
{
	s_eventQueue.push(evt);
}

void MessageQueue::Run(const std::list<Entity*>& entities, OUT SCENE_TYPE& type)
{
	while (s_eventQueue.empty() == false)
	{
		MessageLoop(s_eventQueue.front(), entities, type);

		s_eventQueue.pop();
	}
}

void MessageQueue::MessageLoop(const CLICK_EVENT evt, const std::list<Entity*>& entities, OUT SCENE_TYPE& type)
{

	switch (evt.id)
	{
	case ENTITY_INDEX::Exit:
		exit(0);
		break;
	case ENTITY_INDEX::BazziPickImage:
		OnPickCharacter(entities, evt.isRight, CHARACTER_SELECT_TYPE::Bazzi);
		break;
	case ENTITY_INDEX::DizniPickImage:
		OnPickCharacter(entities, evt.isRight, CHARACTER_SELECT_TYPE::Dizni);
		break;
	case ENTITY_INDEX::RandomPickImage:
		OnPickCharacter(entities, evt.isRight, CHARACTER_SELECT_TYPE::Random);
		break;
	case ENTITY_INDEX::MapPick:
		if (evt.isRight == false)
		{
			for (const auto& entity : entities)
			{
				if (entity->GetId() == ENTITY_INDEX::Map)
				{
					int oldImageIndex = dynamic_cast<DynamicEntity*>(entity)->GetImageIndex();
					dynamic_cast<DynamicEntity*>(entity)->SetImageIndex((oldImageIndex == 1 ? 0 : 1));

					SelectData.mapIndex = (oldImageIndex == 1 ? 0 : 1);
				}
			}
		}
		break;
	case ENTITY_INDEX::Start:
		type = SCENE_TYPE::Loading;
		break;
	default:
		/* For debugging */
		break;
	}
}

void MessageQueue::OnPickCharacter(const std::list<Entity*>& entities, bool isRight, CHARACTER_SELECT_TYPE type)
{
	for (const auto& entity : entities)
	{
		if (entity->GetId() == ENTITY_INDEX::RedCharacter && isRight == false)
		{
			dynamic_cast<DynamicEntity*>(entity)->SetImageIndex((int)type);

			SelectData.redCharacter = (int)type;
		}

		if (entity->GetId() == ENTITY_INDEX::BlueCharacter && isRight == true)
		{
			dynamic_cast<DynamicEntity*>(entity)->SetImageIndex((int)type);

			SelectData.blueCharacter = (int)type;
		}
	}
}
