#pragma once

class Game
{
	DECLARE_SINGLETON(Game);

public:
	bool Init(HWND hwnd);
	void Cleanup();

	void Run();

	void LoadLobby();
	void LoadInGame();
	void LoadMap();
};

