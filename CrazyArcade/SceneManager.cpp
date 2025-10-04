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
		break;
	case SCENE_TYPE::InGame:
		break;
	}

	BitBlt(_hDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, _backDC, 0, 0, SRCCOPY);
}

void SceneManager::LoadLobbyData(const std::vector<IMAGE_DATA*> images)
{
	_lobbyScene->LoadData(images);
}


