#pragma once

class Entity
{
public:
	Entity() = default;
	Entity(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap);
	virtual ~Entity() = default;

	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC dc) = 0;

	void		SetPosition(const VEC2& pos) { _pos = pos; }
	const VEC2& GetPosition() const { return _pos; }
	void		SetSize(const VEC2& size) { _size = size; }
	const VEC2& GetSize() const { return _size; }
	void		SetBitmap(HBITMAP bitmap) { _bitmap = bitmap; }
	HBITMAP		GetBitmap() const { return _bitmap; }

	ENTITY_INDEX GetId() const { return _id; }
	void		 SetOrder(int order) { _order = order; }
	int			 GetOrder() const { return _order; }

protected:
	ENTITY_INDEX _id = ENTITY_INDEX::None;
	HBITMAP		_bitmap = nullptr;
	VEC2		_pos = {};
	VEC2		_size = {};
	int			_order = 0;
};

