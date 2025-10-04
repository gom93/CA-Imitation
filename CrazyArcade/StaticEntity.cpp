#include "pch.h"
#include "StaticEntity.h"

StaticEntity::StaticEntity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap)
	: Entity(id, pos, size, bitmap)
{
	// Background 의 layer 우선순위
	_order = -1;
}

void StaticEntity::Input()
{
}

void StaticEntity::Update()
{
}

void StaticEntity::Render(HDC dc)
{
	SelectObject(dc, _bitmap);

	TransparentBlt(SceneManager::Get().GetBackDC(),
		_pos.x, _pos.y,
		_size.x, _size.y,
		dc,
		0, 0,
		_size.x, _size.y,
		RGB(255, 0, 255));
}
