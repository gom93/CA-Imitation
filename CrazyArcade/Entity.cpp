#include "pch.h"
#include "Entity.h"

Entity::Entity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap)
	: _id(id)
	, _pos(pos)
	, _size(size)
	, _bitmap(bitmap)
{
}


