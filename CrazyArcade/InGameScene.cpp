#include "pch.h"
#include "InGameScene.h"
#include "StaticEntity.h"
#include "DynamicEntity.h"
#include "ButtonEntity.h"
#include "Character.h"
#include "WaterBomb.h"

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

void InGameScene::LoadMapData(const MAP_DATA& mapData)
{

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
