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
	void LoadMapData();

	HWND GetHwnd() const { return _hwnd; }

private:
	HWND _hwnd = nullptr;
};

