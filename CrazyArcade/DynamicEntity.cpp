#include "pch.h"
#include "DynamicEntity.h"

DynamicEntity::DynamicEntity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows)
	: Entity(id, pos, size, bitmap)
	, _cols(cols)
	, _rows(rows)
{
	_imageWidth = size.x / _cols;
	_imageHeight = size.y / _rows;
}

void DynamicEntity::Input()
{
}

void DynamicEntity::Update()
{
}

void DynamicEntity::Render(HDC dc)
{
	if (_cols == 0)
	{
		return;
	}

	SelectObject(dc, _bitmap);

	int cols = _imageIndex % _cols;
	int rows = _imageIndex / _cols;

	TransparentBlt(SceneManager::Get().GetBackDC(),
		_pos.x, _pos.y,
		_imageWidth, _imageHeight,
		dc,
		cols * _imageWidth, rows * _imageHeight,
		_imageWidth, _imageHeight,
		RGB(255, 0, 255));
}

void DynamicEntity::SetImageIndex(int index)
{
	assert(index <= _cols * _rows && index >= 0);

	_imageIndex = index;
}
