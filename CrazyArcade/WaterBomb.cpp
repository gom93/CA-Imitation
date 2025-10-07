#include "pch.h"
#include "WaterBomb.h"

WaterBomb::WaterBomb(ENTITY_INDEX id, const VEC2& pos, const VEC2& size, HBITMAP bitmap, int cols, int rows, int waterLength)
	: DynamicEntity(id, pos, size, bitmap, cols, rows)
	, _waterLength(3)
{
}

void WaterBomb::Input()
{
}

void WaterBomb::Update()
{
	if (_state == BOMB_STATE::Destroy)
	{
		return;
	}

	if (_state == BOMB_STATE::Explosion)
	{
		// 폭발 효과 사라지는 딜레이
		if (CheckPlayAnimation(_animTick, 50) == false)
		{
			return;
		}

		_samplePos.x += _imageWidth;

		// 폭발 해제
		if (_samplePos.x >= _size.x)
		{
			_state = BOMB_STATE::Destroy;
		}
	}

	// 폭발전 딜레이
	if (CheckPlayAnimation(_animTick, 300) == false)
	{
		return;
	}

	_samplePos.x += _imageWidth;

	// 폭발 상태로 변경
	if (_samplePos.x >= _size.x)
	{
		SetExplosionState();
	}
}

void WaterBomb::Render(HDC dc)
{
	SelectObject(dc, _bitmap);

	if (_state != BOMB_STATE::Explosion)
	{
		TransparentBlt(SceneManager::Get().GetBackDC(),
			_pos.x, _pos.y,
			_imageWidth, _imageHeight,
			dc,
			_samplePos.x, _samplePos.y,
			_imageWidth, _imageHeight,
			RGB(0, 0, 0));
	}
	else
	{
		RenderExplosion(dc, _explosionArea.north, DIRECTION::Up);
		RenderExplosion(dc, _explosionArea.south, DIRECTION::Down);
		RenderExplosion(dc, _explosionArea.east, DIRECTION::Right);
		RenderExplosion(dc, _explosionArea.west, DIRECTION::Left);
		RenderExplosion(dc, 1, DIRECTION::Center);
	}
}

void WaterBomb::RenderExplosion(HDC dc, int area, DIRECTION dir)
{
	int explosionImageRowIndex = 0;
	int dx = 0;
	int dy = 0;

	switch ((DIRECTION)dir)
	{
	case DIRECTION::Up:
		explosionImageRowIndex = 5;
		dy = -1;
		break;
	case DIRECTION::Down:
		explosionImageRowIndex = 9;
		dy = 1;
		break;
	case DIRECTION::Right:
		explosionImageRowIndex = 7;
		dx = 1;
		break;
	case DIRECTION::Left:
		explosionImageRowIndex = 3;
		dx = -1;
		break;
	case DIRECTION::Center:
		explosionImageRowIndex = 1;
		break;
	default:
		/* For debugging */
		break;
	}

	for (int i = 1; i <= area; i++)
	{
		// 맨끝 물줄기 모양 출력
		if ((i == _waterLength) && (explosionImageRowIndex != 1))
		{
			_samplePos.y = (explosionImageRowIndex - 1) * _imageHeight;

			TransparentBlt(SceneManager::Get().GetBackDC(),
				_pos.x + (dx * i * BLOCK_WIDTH), _pos.y + (dy * i * BLOCK_WIDTH),
				_imageWidth, _imageHeight,
				dc,
				_samplePos.x, _samplePos.y,
				_imageWidth, _imageHeight,
				RGB(0, 0, 0));
			
			break;
		}

		_samplePos.y = explosionImageRowIndex * _imageHeight;
		
		TransparentBlt(SceneManager::Get().GetBackDC(),
			_pos.x + (dx * i * BLOCK_WIDTH), _pos.y + (dy * i * BLOCK_WIDTH),
			_imageWidth, _imageHeight,
			dc,
			_samplePos.x, _samplePos.y,
			_imageWidth, _imageHeight,
			RGB(0, 0, 0));
	}
}

void WaterBomb::SetMapData(MAP_DATA* mapData)
{
	_mapData = mapData;

	_mapPos.x = (_pos.x - MAP_OFFSET_X) / BLOCK_WIDTH;
	_mapPos.y = (_pos.y - MAP_OFFSET_Y) / BLOCK_HEIGHT;
}

void WaterBomb::SetExplosionState()
{
	_state = BOMB_STATE::Explosion;

	// 물폭탄 애니매이션 프레임 초기화
	_samplePos.x = 0;
	_samplePos.y = 0;

	// 폭발 범위 계산
	SetExplosionArea(_mapPos.x, _mapPos.y, DIRECTION::Up, _explosionArea.north);
	SetExplosionArea(_mapPos.x, _mapPos.y, DIRECTION::Down, _explosionArea.south);
	SetExplosionArea(_mapPos.x, _mapPos.y, DIRECTION::Right, _explosionArea.east);
	SetExplosionArea(_mapPos.x, _mapPos.y, DIRECTION::Left, _explosionArea.west);

	// 물폭탄 맵에서 제거
	_mapData->data[_mapPos.y][_mapPos.x] = (int)MAP_ENTITY::Empty;
}

void WaterBomb::SetExplosionArea(int x, int y, DIRECTION dir, OUT int& area)
{
	int dx = 0;
	int dy = 0;

	switch (dir)
	{
	case DIRECTION::Up:
		dy = -1;
		break;
	case DIRECTION::Down:
		dy = 1;
		break;
	case DIRECTION::Right:
		dx = 1;
		break;
	case DIRECTION::Left:
		dx = -1;
		break;
	}

	for (int len = 1; len <= _waterLength; len++)
	{
		const int nx = x + dx * len;
		const int ny = y + dy * len;
		if (nx < 0 || nx > MAP_WIDTH_SIZE - 1)
		{
			return;
		}
		else if (ny < 0 || ny > MAP_HEIGHT_SIZE - 1)
		{
			return;
		}

		switch ((MAP_ENTITY)_mapData->data[ny][nx])
		{
		case MAP_ENTITY::Empty:
			area++;
			break;
		case MAP_ENTITY::Block:
			_hitBlockPosList.emplace_back(VEC2{ nx, ny });
			return;
		case MAP_ENTITY::Wall:
			return;
		case MAP_ENTITY::WaterBomb:
			area++;
			_hitBombPosList.emplace_back(VEC2{ nx, ny });
			break;
		}
	}
}
