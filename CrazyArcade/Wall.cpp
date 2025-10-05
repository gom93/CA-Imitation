#include "pch.h"
#include "Wall.h"

Wall::Wall(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap)
	: StaticEntity(id, pos, size, bitmap)
{
	_order = pos.y;
}

void Wall::Input()
{
}

void Wall::Update()
{
}
