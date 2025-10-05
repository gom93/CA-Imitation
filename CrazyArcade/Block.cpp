#include "pch.h"
#include "Block.h"

Block::Block(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap)
	: StaticEntity(id, pos, size, bitmap)
{
	_order = pos.y;
}

void Block::Input()
{
}

void Block::Update()
{
}
