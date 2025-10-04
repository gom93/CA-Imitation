#pragma once

#include "Entity.h"

class ButtonEntity : public Entity
{
public:
	ButtonEntity() = default;
	ButtonEntity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap);
	virtual ~ButtonEntity() = default;

	virtual void Input() override;
	virtual void Update() override;
	virtual void Render(HDC dc) override;
};

