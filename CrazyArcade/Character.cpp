#include "pch.h"
#include "Character.h"

Character::Character(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows, const CHARACTER_STAT& stats)
	: DynamicEntity(id, pos, size, bitmap, cols, rows)
	, _stats(stats)
{
	Init();
}

bool Character::Init()
{
	switch (_id)
	{
	case ENTITY_INDEX::RedBazzi:
		_color = TEAM_COLOR::Red;
		_name = CHARACTER_NAME::Bazzi;
		break;
	case ENTITY_INDEX::RedDizni:
		_color = TEAM_COLOR::Red;
		_name = CHARACTER_NAME::Dizni;
		break;
	case ENTITY_INDEX::BlueBazzi:
		_color = TEAM_COLOR::Blue;
		_name = CHARACTER_NAME::Bazzi;
		break;
	case ENTITY_INDEX::BlueDizni:
		_color = TEAM_COLOR::Blue;
		_name = CHARACTER_NAME::Dizni;
		break;
	default:
		/* For debugging */
		break;
	}

	return true;
}