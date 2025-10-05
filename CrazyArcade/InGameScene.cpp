#include "pch.h"
#include "InGameScene.h"
#include "StaticEntity.h"
#include "DynamicEntity.h"
#include "ButtonEntity.h"
#include "Character.h"
#include "WaterBomb.h"
#include "Block.h"
#include "Wall.h"

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
			_allEntites.emplace_back(_inGameEntites.back());
			break;
		case ENTITY_TYPE::Dynamic:

			_inGameEntites.emplace_back(new DynamicEntity(
				(ENTITY_INDEX)image->id,
				VEC2{ image->x, image->y },
				VEC2{ bitmap.bmWidth, bitmap.bmHeight },
				image->bitmap,
				image->cols, image->rows));
			_allEntites.emplace_back(_inGameEntites.back());
			break;
		case ENTITY_TYPE::Button:
			_inGameEntites.emplace_back(new ButtonEntity(
				(ENTITY_INDEX)image->id,
				VEC2{ image->x, image->y },
				VEC2{ bitmap.bmWidth, bitmap.bmHeight },
				image->bitmap,
				image->cols, image->rows));
			_allEntites.emplace_back(_inGameEntites.back());
			break;
		default:
			// 拱气藕, 寒 殿... 蝶肺 包府
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

	_allEntites.emplace_back(_characters.back());
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
				_allEntites.emplace_back(_inGameEntites.back());
				break;
			case MAP_ENTITY::Wall:
				_inGameEntites.emplace_back(new Wall(
					(ENTITY_INDEX)_entityDatas[1]->id,
					VEC2{ _entityDatas[1]->x + col * _entityBitmap[1].bmWidth, _entityDatas[1]->y + row * _entityBitmap[1].bmHeight },
					VEC2{ _entityBitmap[1].bmWidth, _entityBitmap[1].bmHeight },
					_entityDatas[1]->bitmap
				));
				_allEntites.emplace_back(_inGameEntites.back());
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

	for (WaterBomb* waterBomb : _waterBombs)
	{
		waterBomb->Update();
	}

	for (Character* character : _characters)
	{
		character->Input();
		CreateBomb(character);
		character->Update();
		character->FinalUpdate();
	}

	for (Entity* entity : _allEntites)
	{
		entity->Render(dc);
	}
}

void InGameScene::CreateBomb(Character* character)
{
	ATTACK_HANDLE& attack = character->GetAttackHandle();
	if (attack.isAttack)
	{
		attack.isAttack = false;

		// 拱气藕 积己
		_waterBombs.emplace_back(new WaterBomb(
			(ENTITY_INDEX)_entityDatas[2]->id,
			VEC2{ attack.pos.x, attack.pos.y },
			VEC2{ _entityBitmap[2].bmWidth, _entityBitmap[2].bmHeight },
			_entityDatas[2]->bitmap,
			_entityDatas[2]->cols,
			_entityDatas[2]->rows,
			character->GetWaterBombLength()
		));

		_allEntites.emplace_back(_waterBombs.back());
	}
}
