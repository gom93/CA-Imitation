#pragma once

#include "Entity.h"

class StaticEntity : public Entity
{
public:
	StaticEntity() = default;
	StaticEntity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap);
	virtual ~StaticEntity() = default;

	virtual void Input() override;
	virtual void Update() override;
	virtual void Render(HDC dc) override;
};

