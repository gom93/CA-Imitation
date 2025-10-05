#include "pch.h"
#include "Character.h"

Character::Character(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows, const CHARACTER_STAT& stats)
	: DynamicEntity(id, pos, size, bitmap, cols, rows)
	, _stats(stats)
{
	Init();
}

bool Character::Init()
{
	switch (_id)
	{
	case ENTITY_INDEX::RedBazzi:
		_color = TEAM_COLOR::Red;
		_name = CHARACTER_NAME::Bazzi;
		break;
	case ENTITY_INDEX::RedDizni:
		_color = TEAM_COLOR::Red;
		_name = CHARACTER_NAME::Dizni;
		break;
	case ENTITY_INDEX::BlueBazzi:
		_color = TEAM_COLOR::Blue;
		_name = CHARACTER_NAME::Bazzi;
		break;
	case ENTITY_INDEX::BlueDizni:
		_color = TEAM_COLOR::Blue;
		_name = CHARACTER_NAME::Dizni;
		break;
	default:
		/* For debugging */
		break;
	}

	_animTick = GetTickCount64();

	return true;
}

void Character::Input()
{
	switch (_color)
	{
	case TEAM_COLOR::Red:
		if (GetAsyncKeyState(VK_UP))
		{
			_dir = DIRECTION::Up;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			_dir = DIRECTION::Down;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			_dir = DIRECTION::Left;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			_dir = DIRECTION::Right;
		}
		if (_isAttackable && _stats.bombNum > _installedBombNum)
		{
			if ((GetAsyncKeyState(VK_RSHIFT) & 0x0001) && _isDirtyFlag)
			{
				_attack.pos.x = _pos.x;
				_attack.pos.y = _pos.y + _imageHeight / 2;
				_attack.isAttack = true;

				_installedBombNum++;

				_isDirtyFlag = false;
			}
			else
			{
				_isDirtyFlag = true;
			}
		}
		break;
	case TEAM_COLOR::Blue:
		if (GetAsyncKeyState('W'))
		{
			_dir = DIRECTION::Up;
		}
		if (GetAsyncKeyState('S'))
		{
			_dir = DIRECTION::Down;
		}
		if (GetAsyncKeyState('A'))
		{
			_dir = DIRECTION::Left;
		}
		if (GetAsyncKeyState('D'))
		{
			_dir = DIRECTION::Right;
		}
		break;
	}
}

void Character::Update()
{
	switch (_dir)
	{
	case DIRECTION::Left:
		_pos.x -= _stats.speed;
		break;
	case DIRECTION::Right:
		_pos.x += _stats.speed;
		break;
	case DIRECTION::Down:
		_pos.y += _stats.speed;
		break;
	case DIRECTION::Up:
		_pos.y -= _stats.speed;
		break;
	}

	PlayAnimation(_dir);
}

void Character::Render(HDC dc)
{
	SelectObject(dc, _bitmap);

	TransparentBlt(SceneManager::Get().GetBackDC(),
		_pos.x, _pos.y,
		_imageWidth, _imageHeight,
		dc,
		_samplePos.x, _samplePos.y,
		_imageWidth, _imageHeight,
		RGB(255, 0, 255));
}

void Character::FinalUpdate()
{
	_dir = DIRECTION::Center;
}

void Character::PlayAnimation(DIRECTION dir)
{
	switch (_dir)
	{
	case DIRECTION::Left:
		if (CheckPlayAnimation(_animTick, 100) == true)
		{
			_samplePos.x += _imageWidth;
			_samplePos.y = 0;
			if (_samplePos.x >= _size.x)
			{
				_samplePos.x = 0;
			}
		}
		break;
	case DIRECTION::Up:
		if (CheckPlayAnimation(_animTick, 100) == true)
		{
			_samplePos.x += _imageWidth;
			_samplePos.y = _imageHeight;
			if (_samplePos.x >= _size.x)
			{
				_samplePos.x = 0;
			}
		}
		break;
	case DIRECTION::Right:
		if (CheckPlayAnimation(_animTick, 100) == true)
		{
			_samplePos.x += _imageWidth;
			_samplePos.y = _imageHeight * 2;
			if (_samplePos.x >= _size.x)
			{
				_samplePos.x = 0;
			}
		}
		break;
	case DIRECTION::Down:
		if (CheckPlayAnimation(_animTick, 100) == true)
		{
			_samplePos.x += _imageWidth;
			_samplePos.y = _imageHeight * 3;
			if (_samplePos.x >= _size.x)
			{
				_samplePos.x = 0;
			}
		}
		break;
	}
}
