#pragma once

#include "DynamicEntity.h"

class Character : public DynamicEntity
{
public:
	Character() = default;
	Character(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows, const CHARACTER_STAT& stats);
	virtual ~Character() = default;

	bool Init();

private:
	CHARACTER_STAT	_stats = {};
	TEAM_COLOR		_color = TEAM_COLOR::Red;
	CHARACTER_STATE _state = CHARACTER_STATE::Normal;
	CHARACTER_NAME	_name = CHARACTER_NAME::Bazzi;
	VEC2			_samplePos = {};
};

