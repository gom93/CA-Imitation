#include "pch.h"
#include "Game.h"

bool Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	SceneManager::Get().Init(hwnd);
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
}

void Game::LoadLobby()
{
	ImageManager::Get().LoadImageData();
	SceneManager::Get().LoadLobbyData(ImageManager::Get().GetLobbyImages());
}

void Game::LoadInGame()
{
}

void Game::LoadMap()
{
}
