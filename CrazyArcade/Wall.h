#pragma once

#include "StaticEntity.h"

class Wall : public StaticEntity
{
public:
	Wall() = default;
	Wall(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap);
	virtual ~Wall() = default;

	virtual void Input() override;
	virtual void Update() override;
};

