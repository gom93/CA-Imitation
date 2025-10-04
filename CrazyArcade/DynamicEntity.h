#pragma once
#include "Entity.h"
class DynamicEntity :
    public Entity
{
public:
	DynamicEntity() = default;
	DynamicEntity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows);
	virtual ~DynamicEntity() = default;

	virtual void Input() override;
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	void	SetImageIndex(int index);
	int		GetImageIndex() const { return _imageIndex; }

protected:
	int _cols = 0;
	int _rows = 0;
	int _imageWidth = 0;
	int _imageHeight = 0;
	int _imageIndex = 0;
};

