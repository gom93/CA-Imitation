#include "pch.h"
#include "InGameScene.h"
#include "StaticEntity.h"
#include "DynamicEntity.h"
#include "ButtonEntity.h"
#include "Character.h"

void InGameScene::LoadInGameData(const std::vector<IMAGE_DATA*> images)
{
	BITMAP bitmap;
	for (IMAGE_DATA* image : images)
	{
		GetObject(image->bitmap, sizeof(BITMAP), &bitmap);
		switch ((ENTITY_TYPE)image->type)
		{
		case ENTITY_TYPE::Static:
			_entities.emplace_back(new StaticEntity(
				(ENTITY_INDEX)image->id,
				VEC2{ image->x, image->y },
				VEC2{ bitmap.bmWidth, bitmap.bmHeight },
				image->bitmap));

			break;
		case ENTITY_TYPE::Dynamic:

			_entities.emplace_back(new DynamicEntity(
				(ENTITY_INDEX)image->id,
				VEC2{ image->x, image->y },
				VEC2{ bitmap.bmWidth, bitmap.bmHeight },
				image->bitmap,
				image->cols, image->rows));

			break;
		case ENTITY_TYPE::Button:
			_entities.emplace_back(new ButtonEntity(
				(ENTITY_INDEX)image->id,
				VEC2{ image->x, image->y },
				VEC2{ bitmap.bmWidth, bitmap.bmHeight },
				image->bitmap,
				image->cols, image->rows));
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
}

void InGameScene::LoadItemData(const std::vector<IMAGE_DATA*> images)
{
}

void InGameScene::LoadMapData(const MAP_DATA& mapData)
{

}

void InGameScene::Process(HDC dc)
{
	for (Entity* entity : _entities)
	{
		entity->Input();
		entity->Update();
	}

	for (Character* character : _characters)
	{
		character->Render(dc);
	}
}
