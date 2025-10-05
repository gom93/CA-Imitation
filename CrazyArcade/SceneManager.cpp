#include "pch.h"
#include "SceneManager.h"
#include "LobbyScene.h"
#include "InGameScene.h"

bool SceneManager::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hDC = GetDC(_hwnd);
	_memDC = CreateCompatibleDC(_hDC);
	_backDC = CreateCompatibleDC(_hDC);
	_lobbyScene = new LobbyScene;
	_inGameScene = new InGameScene;
	return true;
}

void SceneManager::Cleanup()
{
	delete _inGameScene;
	delete _lobbyScene;
	DeleteDC(_backDC);
	DeleteDC(_memDC);
	ReleaseDC(_hwnd, _hDC);
}

void SceneManager::Process()
{
	if (_oldBitmap)
	{
		DeleteObject(_oldBitmap);
		_oldBitmap = nullptr;
	}

	_oldBitmap = (HBITMAP)SelectObject(_backDC, CreateCompatibleBitmap(_hDC, SCREEN_WIDTH, SCREEN_HEIGHT));

	/*
	HBRUSH hBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	FillRect(_backDC, &rc, hBrush);
	*/

	switch (_sceneType)
	{
	case SCENE_TYPE::Lobby:
		_lobbyScene->Process(_memDC);
		MessageQueue::Run(_lobbyScene->GetEntities(), _sceneType);
		_selectData = _lobbyScene->GetSelectData();
		break;
	case SCENE_TYPE::InGame:
		_inGameScene->Process(_memDC);
		break;
	}

	BitBlt(_hDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, _backDC, 0, 0, SRCCOPY);
}

void SceneManager::LoadLobbyData(const std::vector<IMAGE_DATA*> images)
{
	_lobbyScene->LoadData(images);
}

void SceneManager::LoadInGameData(const std::vector<IMAGE_DATA*> images)
{
	_inGameScene->LoadInGameData(images);
}

void SceneManager::LoadCharacterData(const IMAGE_DATA** images, const CHARACTER_STAT* state)
{
	for (UINT i = 0; i < 2; i++)
	{
		_inGameScene->LoadCharacterData(images[i], /*Trapped Image*/images[2], /*Die Image*/images[3], state[i]);
	}
}

void SceneManager::LoadItemData(const std::vector<IMAGE_DATA*> images)
{
	_inGameScene->LoadItemData(images);
}

void SceneManager::LoadMapData(const MAP_DATA& mapData)
{
	_inGameScene->SetMapData(mapData);
	_inGameScene->LoadStaticEntityData();
}



