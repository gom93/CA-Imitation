#pragma once

#include "DynamicEntity.h"

enum class BOMB_STATE
{
	Default,
	Explosion,
	Destroy
};

struct EXPLOSION_AREA
{
	int north = 0;
	int west = 0;
	int east = 0;
	int south = 0;
};

class WaterBomb : public DynamicEntity
{
public:
	WaterBomb(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows, int waterLength);
	virtual ~WaterBomb() = default;

	virtual void Input() override;
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	void		RenderExplosion(HDC dc, int area, DIRECTION dir);

	void		SetMapData(const MAP_DATA* mapData);
	BOMB_STATE	GetState() const { return _state; }
	void		SetColor(TEAM_COLOR color) { _color = color; }
	TEAM_COLOR	GetColor() const { return _color; }

private:
	void		SetExplosionState();
	void		SetExplosionArea(int x, int y, DIRECTION dir, OUT int& area);

private:
	int					_waterLength = 0;
	BOMB_STATE			_state = BOMB_STATE::Default;
	EXPLOSION_AREA		_explosionArea = {};
	const MAP_DATA*		_mapData = nullptr;
	VEC2				_mapPos = {};
	std::vector<VEC2>	_hitBlockPosList = {};
	std::vector<VEC2>	_hitBombPosList = {};
	TEAM_COLOR			_color = TEAM_COLOR::None;
};

