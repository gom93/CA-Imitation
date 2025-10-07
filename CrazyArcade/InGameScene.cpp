#include "pch.h"
#include "InGameScene.h"
#include "StaticEntity.h"
#include "DynamicEntity.h"
#include "ButtonEntity.h"
#include "Character.h"
#include "WaterBomb.h"
#include "Block.h"
#include "Wall.h"

VEC2 InGameScene::_eraseBombPos = {};

void InGameScene::LoadInGameData(const std::vector<IMAGE_DATA*> images)
{
	BITMAP bitmap;
	for (IMAGE_DATA* image : images)
	{
		GetObject(image->bitmap, sizeof(BITMAP), &bitmap);
		switch ((ENTITY_TYPE)image->type)
		{
		case ENTITY_TYPE::Static:
			_inGameEntites.emplace_back(new StaticEntity(
				(ENTITY_INDEX)image->id,
				VEC2{ image->x, image->y },
				VEC2{ bitmap.bmWidth, bitmap.bmHeight },
				image->bitmap));
			_allEntities.emplace_back(_inGameEntites.back());
			break;
		case ENTITY_TYPE::Dynamic:

			_inGameEntites.emplace_back(new DynamicEntity(
				(ENTITY_INDEX)image->id,
				VEC2{ image->x, image->y },
				VEC2{ bitmap.bmWidth, bitmap.bmHeight },
				image->bitmap,
				image->cols, image->rows));
			_allEntities.emplace_back(_inGameEntites.back());
			break;
		case ENTITY_TYPE::Button:
			_inGameEntites.emplace_back(new ButtonEntity(
				(ENTITY_INDEX)image->id,
				VEC2{ image->x, image->y },
				VEC2{ bitmap.bmWidth, bitmap.bmHeight },
				image->bitmap,
				image->cols, image->rows));
			_allEntities.emplace_back(_inGameEntites.back());
			break;
		default:
			// 물폭탄, 벽 등... 따로 관리
			_entityDatas.emplace_back(image);
			_entityBitmap.emplace_back(bitmap);
			break;
		}
	}
}

void InGameScene::LoadCharacterData(const IMAGE_DATA* characterImage, const IMAGE_DATA* trappedImage, const IMAGE_DATA* dieImage, const CHARACTER_STAT& characterStats)
{
	BITMAP bitmap;
	GetObject(characterImage->bitmap, sizeof(BITMAP), &bitmap);

	_characters.emplace_back(new Character(
		(ENTITY_INDEX)characterImage->id,
		VEC2{ characterImage->x, characterImage->y },
		VEC2{ bitmap.bmWidth, bitmap.bmHeight },
		characterImage->bitmap,
		characterImage->cols, characterImage->rows,
		characterStats
	));

	_allEntities.emplace_back(_characters.back());
}

void InGameScene::LoadItemData(const std::vector<IMAGE_DATA*> images)
{
}

void InGameScene::SetMapData(const MAP_DATA& mapData)
{
	_mapData = mapData;
}

void InGameScene::LoadStaticEntityData()
{
	for (int row = 0; row < MAP_HEIGHT_SIZE; row++)
	{
		for (int col = 0; col < MAP_WIDTH_SIZE; col++)
		{
			switch ((MAP_ENTITY)_mapData.data[row][col])
			{
			case MAP_ENTITY::Block:
				_inGameEntites.emplace_back(new Block(
					(ENTITY_INDEX)_entityDatas[0]->id,
					VEC2{ _entityDatas[0]->x + col * _entityBitmap[0].bmWidth, _entityDatas[0]->y + row * _entityBitmap[0].bmHeight},
					VEC2{ _entityBitmap[0].bmWidth, _entityBitmap[0].bmHeight },
					_entityDatas[0]->bitmap
				));
				_allEntities.emplace_back(_inGameEntites.back());
				break;
			case MAP_ENTITY::Wall:
				_inGameEntites.emplace_back(new Wall(
					(ENTITY_INDEX)_entityDatas[1]->id,
					// Wall Size 와 Block Size 차이로 SIZE_TUNING 진행
					VEC2{ _entityDatas[1]->x + col * _entityBitmap[0].bmWidth, _entityDatas[1]->y + row * _entityBitmap[0].bmHeight - WALL_SIZE_TUNING },
					VEC2{ _entityBitmap[1].bmWidth, _entityBitmap[1].bmHeight },
					_entityDatas[1]->bitmap
				));
				_allEntities.emplace_back(_inGameEntites.back());
				break;
			}
		}
	}
}

void InGameScene::Process(HDC dc)
{
	for (Entity* inGameEntity : _inGameEntites)
	{
		inGameEntity->Input();
		inGameEntity->Update();
	}

	DestroyBombs();

	for (WaterBomb* waterBomb : _waterBombs)
	{
		waterBomb->Update();

		if (BOMB_STATE::Explosion == waterBomb->GetState())
		{
			if (_isExplosion == false)
			{
				AudioManager::Get().PlayEffectSound(EFFECT_SOUND::Explosion);
				_isExplosion = true;
			}

			DestroyHitEntity(waterBomb->GetBombPosList());
		}

		if (BOMB_STATE::Destroy == waterBomb->GetState())
		{
			DestroyHitEntity(waterBomb->GetBlockPosList());
		}
	}

	for (Character* character : _characters)
	{
		character->Input();
		CreateBomb(character);
		character->Update();
		character->FinalUpdate(_inGameEntites);
	}

	_allEntities.sort(SortEntity);
	for (Entity* entity : _allEntities)
	{
		entity->Render(dc);
	}
}

void InGameScene::DestroyHitEntity(const std::vector<VEC2>& hitPos)
{
	int hitEntity = 0;
	for (const VEC2& pos : hitPos)
	{
		// 충돌한 위치의 Entity 가 Block 또는 WaterBomb 일 경우
		if (_mapData.data[pos.y][pos.x] == (int)MAP_ENTITY::Block || _mapData.data[pos.y][pos.x] == (int)MAP_ENTITY::WaterBomb)
		{
			// 해당 Entity 의 타입을 저장하고, 맵에서 제거
			hitEntity = _mapData.data[pos.y][pos.x];
			_mapData.data[pos.y][pos.x] = (int)MAP_ENTITY::Empty;
		}
	}

	// 물폭탄일 경우
	if ((int)MAP_ENTITY::Empty == hitEntity)
	{
		for (WaterBomb* bomb : _waterBombs)
		{
			for (const VEC2& pos : hitPos)
			{
				if (bomb->GetPosInMap() == pos)
				{
					bomb->SetExplosionState();
				}
			}
		}
		return;
	}

	// Entity 삭제 
	// 물폭탄의 경우 DestroyBombs() 함수에서 삭제를 담당
	VEC2 mapPos = {};
	for (const VEC2& pos : hitPos)
	{
		std::list<Entity*>::iterator iter = _inGameEntites.begin();
		for (; iter != _inGameEntites.end();)
		{
			mapPos.x = ((*iter)->GetPosition().x - MAP_OFFSET_X) / BLOCK_WIDTH;
			mapPos.y = ((*iter)->GetPosition().y - MAP_OFFSET_Y) / BLOCK_HEIGHT;

			if (mapPos == pos && (*iter)->GetId() == ENTITY_INDEX::Block)
			{
				_allEntities.remove_if([&](const Entity* entityPos)->bool {
					return entityPos->GetPosition().x == (*iter)->GetPosition().x && entityPos->GetPosition().y == (*iter)->GetPosition().y;
					});

				delete (*iter);
				iter = _inGameEntites.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}
}

void InGameScene::CreateBomb(Character* character)
{
	ATTACK_HANDLE& attack = character->GetAttackHandle();
	if (attack.isAttack)
	{
		attack.isAttack = false;

		// 물폭탄 생성
		_waterBombs.emplace_back(new WaterBomb(
			(ENTITY_INDEX)_entityDatas[2]->id,
			VEC2{ attack.pos.x, attack.pos.y },
			VEC2{ _entityBitmap[2].bmWidth, _entityBitmap[2].bmHeight },
			_entityDatas[2]->bitmap,
			_entityDatas[2]->cols,
			_entityDatas[2]->rows,
			character->GetWaterBombLength()
		));

		_waterBombs.back()->SetColor(attack.color);

		_waterBombs.back()->SetMapData(&_mapData);

		_allEntities.emplace_back(_waterBombs.back());
	}
}

void InGameScene::DestroyBombs()
{
	std::list<WaterBomb*>::iterator iter = _waterBombs.begin();
	for (; iter != _waterBombs.end();)
	{
		if (BOMB_STATE::Destroy == (*iter)->GetState())
		{
			switch ((*iter)->GetColor())
			{
			case TEAM_COLOR::Red:
				for (Character* character : _characters)
				{
					if (character->GetColor() == (*iter)->GetColor())
					{
						character->DecreaseBombNum();
					}
				}
				break;
			case TEAM_COLOR::Blue:
				for (Character* character : _characters)
				{
					if (character->GetColor() == (*iter)->GetColor())
					{
						character->DecreaseBombNum();
					}
				}
				break;
			}

			_isExplosion = false;
			_eraseBombPos = (*iter)->GetPosition();
			_allEntities.remove_if(EraseBomb);

			delete (*iter);
			iter = _waterBombs.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

bool InGameScene::EraseBomb(Entity* entity)
{
	return (entity->GetPosition().x == _eraseBombPos.x) && (entity->GetPosition().y == _eraseBombPos.y);
}

bool InGameScene::SortEntity(Entity* a, Entity* b)
{
	return a->GetOrder() < b->GetOrder();
}
