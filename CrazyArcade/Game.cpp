#include "pch.h"
#include "Game.h"

bool Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	SceneManager::Get().Init(hwnd);
	AudioManager::Get().Init();
	AudioManager::Get().PlaySoundTrack(BGM::Room);

	return true;
}

void Game::Cleanup()
{
	SceneManager::Get().Cleanup();
	ImageManager::Get().Cleanup();
}

void Game::Run()
{
	SceneManager::Get().Process();

	SCENE_TYPE type = SceneManager::Get().GetSceneType();
	switch (type)
	{
	case SCENE_TYPE::Loading:
		LoadInGame();
		SceneManager::Get().SetSceneType(SCENE_TYPE::InGame);
		break;
	case SCENE_TYPE::Existing:
		
		break;
	}
}

void Game::LoadLobby()
{
	ImageManager::Get().LoadImageData();
	SceneManager::Get().LoadLobbyData(ImageManager::Get().GetLobbyImages());
}

void Game::LoadInGame()
{
	SceneManager::Get().LoadInGameData(ImageManager::Get().GetInGameImages());
	SceneManager::Get().LoadCharacterData(ImageManager::Get().GetCharacterImage(SceneManager::Get().GetSelectData()), ImageManager::Get().GetCharacterStats(SceneManager::Get().GetSelectData()));
	SceneManager::Get().LoadMapData(MapManager::Get().LoadMap(SceneManager::Get().GetSelectData()));
}

void Game::LoadMapData()
{
	MapManager::Get().LoadMapDataFromFile();
}
