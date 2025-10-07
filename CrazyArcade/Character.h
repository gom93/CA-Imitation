#pragma once

#include "DynamicEntity.h"

struct ATTACK_HANDLE
{
	bool isAttack;
	TEAM_COLOR color;
	VEC2 pos;
};

class Character : public DynamicEntity
{
public:
	Character() = default;
	Character(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows, const CHARACTER_STAT& stats);
	virtual ~Character() = default;

	bool Init();

	virtual void Input() override;
	virtual void Update() override;
	virtual void Render(HDC dc) override;

	void			FinalUpdate(const std::list<Entity*>& inGameEntities);

	ATTACK_HANDLE&	GetAttackHandle() { return _attack; }
	int				GetWaterBombLength() { return _stats.bombLength; }
	TEAM_COLOR		GetColor() const { return _color; }

	void			DecreaseBombNum();

private:
	void			PlayAnimation(DIRECTION dir);
	void			SetBombPosition();
	void			CheckBorder();
	void			CheckMove(const std::list<Entity*>& inGameEntities);

	bool			CheckCollision(const RECT& a, const RECT& b);
	RECT			ConvertToRect(const VEC2& pos, bool tuning);

private:
	CHARACTER_STAT	_stats = {};
	TEAM_COLOR		_color = TEAM_COLOR::Red;
	CHARACTER_STATE _state = CHARACTER_STATE::Normal;
	CHARACTER_NAME	_name = CHARACTER_NAME::Bazzi;
	DIRECTION		_dir = DIRECTION::Up;
	bool			_isAttackable = true;
	int				_installedBombNum = 0;
	bool			_isDirtyFlag = true;
	ATTACK_HANDLE	_attack = {};
};

