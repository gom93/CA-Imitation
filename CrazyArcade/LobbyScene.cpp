#include "pch.h"
#include "LobbyScene.h"
#include "StaticEntity.h"
#include "DynamicEntity.h"
#include "ButtonEntity.h"

void LobbyScene::LoadData(const std::vector<IMAGE_DATA*> images)
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
				VEC2 { image->x, image->y }, 
				VEC2 { bitmap.bmWidth, bitmap.bmHeight }, 
				image->bitmap));

			break;
		case ENTITY_TYPE::Dynamic:

			_entities.emplace_back(new DynamicEntity(
				(ENTITY_INDEX)image->id, 
				VEC2 { image->x, image->y }, 
				VEC2 { bitmap.bmWidth, bitmap.bmHeight }, 
				image->bitmap, 
				image->cols, image->rows));

			break;
		case ENTITY_TYPE::Button:
			_entities.emplace_back(new ButtonEntity(
				(ENTITY_INDEX)image->id, 
				VEC2 { image->x, image->y }, 
				VEC2{ bitmap.bmWidth, bitmap.bmHeight }, 
				image->bitmap, 
				image->cols, image->rows));
			break;
		}
	}
}

void LobbyScene::Process(HDC dc)
{
	for (Entity* entity : _entities)
	{
		entity->Input();
		entity->Update();
		entity->Render(dc);
	}
}
