#pragma once

#include "StaticEntity.h"

class Block : public StaticEntity
{
public:
	Block() = default;
	Block(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap);
	virtual ~Block() = default;

	virtual void Input() override;
	virtual void Update() override;
};

