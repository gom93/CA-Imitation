#pragma once
#include "Entity.h"
class DynamicEntity :
    public Entity
{
public:
	DynamicEntity() = default;
	DynamicEntity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap);
	virtual ~DynamicEntity() = default;

	virtual void Input() override;
	virtual void Update() override;
	virtual void Render(HDC dc) override;
};

