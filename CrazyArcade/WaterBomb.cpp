#include "pch.h"
#include "WaterBomb.h"

WaterBomb::WaterBomb(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows, int waterLength)
	: DynamicEntity(id, pos, size, bitmap, cols, rows)
	, _waterLength(waterLength)
{
}

void WaterBomb::Input()
{
}

void WaterBomb::Update()
{
	if (CheckPlayAnimation(_animTick, 300) == false)
	{
		return;
	}

	_samplePos.x += _imageWidth;
	// 폭발 상태로 변경
	if (_samplePos.x >= _size.x)
	{
		SetExplosionState();
	}
}

void WaterBomb::Render(HDC dc)
{
	SelectObject(dc, _bitmap);

	TransparentBlt(SceneManager::Get().GetBackDC(),
		_pos.x, _pos.y,
		_imageWidth, _imageHeight,
		dc,
		_samplePos.x, _samplePos.y,
		_imageWidth, _imageHeight,
		RGB(0, 0, 0));
}

void WaterBomb::SetExplosionState()
{
	_state = BOMB_STATE::Explosion;
	_samplePos.x = 0;


}
