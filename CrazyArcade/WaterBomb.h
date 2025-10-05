#pragma once

#include "DynamicEntity.h"

enum class BOMB_STATE
{
	Default,
	Explosion,
	Destroy
};

class WaterBomb : public DynamicEntity
{
public:
	WaterBomb(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows, int waterLength);
	virtual ~WaterBomb() = default;

	virtual void Input() override;
	virtual void Update() override;
	virtual void Render(HDC dc) override;

private:
	void SetExplosionState();

private:
	int			_waterLength = 0;
	BOMB_STATE  _state = BOMB_STATE::Default;
};

