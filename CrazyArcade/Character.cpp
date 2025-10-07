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
				_attack.pos.y = _pos.y;
				SetBombPosition();

				_attack.isAttack = true;
				_attack.color = _color;

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

void Character::FinalUpdate(const std::list<Entity*>& inGameEntities)
{
	CheckBorder();
	CheckMove(inGameEntities);

	_dir = DIRECTION::Center;
}

void Character::DecreaseBombNum()
{
	assert(_installedBombNum > 0);
	_installedBombNum--;
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

void Character::SetBombPosition()
{
	int epsilon = (_attack.pos.x + MAP_OFFSET_X) % BLOCK_WIDTH;

	// X 위치가 사이에 Block 사이에 위치해 있을 경우
	if (epsilon != 0)
	{
		if (epsilon >= BLOCK_WIDTH / 2)
		{
			_attack.pos.x = _attack.pos.x + (BLOCK_WIDTH - epsilon);
		}
		else
		{
			_attack.pos.x = _attack.pos.x - epsilon;
		}
	}

	epsilon = (_attack.pos.y + MAP_OFFSET_Y) % BLOCK_HEIGHT;

	// Y 위치가 사이에 Block 사이에 위치해 있을 경우
	if (epsilon != 0)
	{
		if (epsilon >= BLOCK_HEIGHT / 2)
		{
			_attack.pos.y = _attack.pos.y + (BLOCK_HEIGHT - epsilon);
		}
		else
		{
			_attack.pos.y = _attack.pos.y - epsilon;
		}
	}
}

void Character::CheckBorder()
{
	// X
	if (_pos.x <= MAP_OFFSET_X)
	{
		_pos.x = MAP_OFFSET_X;
	}
	else if (_pos.x >= (MAP_WIDTH_SIZE * BLOCK_WIDTH - BLOCK_WIDTH / 2))
	{
		_pos.x = (MAP_WIDTH_SIZE * BLOCK_WIDTH - BLOCK_WIDTH / 2);
	}

	// Y
	if (_pos.y <= MAP_OFFSET_Y)
	{
		_pos.y = MAP_OFFSET_Y;
	}
	else if (_pos.y >= (MAP_HEIGHT_SIZE * BLOCK_HEIGHT - BLOCK_HEIGHT / 2))
	{
		_pos.y = (MAP_HEIGHT_SIZE * BLOCK_HEIGHT - BLOCK_HEIGHT / 2);
	}
}

void Character::CheckMove(const std::list<Entity*>& inGameEntities)
{
	RECT ownRect =
	{
		_pos.x, _pos.y,
		(LONG)(_pos.x + BLOCK_WIDTH), 
		(LONG)(_pos.y + BLOCK_HEIGHT)
	};

	RECT entityRect = {};
	for (Entity* entity : inGameEntities)
	{
		if (entity->GetId() == ENTITY_INDEX::Background)
		{
			continue;
		}
		else if (entity->GetId() == ENTITY_INDEX::Block)
		{
			entityRect = ConvertToRect(entity->GetPosition(), true);
		}
		else if (entity->GetId() == ENTITY_INDEX::Wall)
		{
			entityRect = ConvertToRect(entity->GetPosition(), false);
		}

		if (CheckCollision(ownRect, entityRect))
		{
			switch (_dir)
			{
			case DIRECTION::Up:
				if (entityRect.right > ownRect.left)
				{
					_pos.x++;
				}
				else if (entityRect.left < ownRect.left)
				{
					_pos.x--;
				}
				_pos.y = entityRect.bottom;
				break;
			case DIRECTION::Down:
				if (entityRect.right > ownRect.left)
				{
					_pos.x++;
				}
				else if (entityRect.left < ownRect.left)
				{
					_pos.x--;
				}
				_pos.y = entityRect.top - BLOCK_HEIGHT;
				break;
			case DIRECTION::Left:
				if (entityRect.bottom > ownRect.top)
				{
					_pos.y++;
				}
				else if (entityRect.top < ownRect.bottom)
				{
					_pos.y--;
				}
				_pos.x = entityRect.right;
				break;
			case DIRECTION::Right:
				if (entityRect.bottom > ownRect.top)
				{
					_pos.y++;
				}
				else if (entityRect.bottom < ownRect.top)
				{
					_pos.y--;
				}
				_pos.x = entityRect.left - BLOCK_WIDTH;
				break;
			}
		}
	}
}

bool Character::CheckCollision(const RECT& a, const RECT& b)
{
	if (a.left < b.left && a.right > b.left &&
		a.top < b.bottom && a.bottom > b.top)
	{
		return true;
	}
	return false;
}

RECT Character::ConvertToRect(const VEC2& pos, bool tuning)
{
	RECT rt = {};
	rt.left = pos.x;
	rt.top = tuning ? pos.y - WALL_SIZE_TUNING : pos.y;
	rt.right = pos.x + BLOCK_WIDTH;
	rt.bottom = tuning ? pos.y + BLOCK_HEIGHT - WALL_SIZE_TUNING : pos.y + BLOCK_HEIGHT;
	return rt;
}
