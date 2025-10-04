#pragma once

class LobbyScene;
class InGameScene;

class SceneManager
{
	DECLARE_SINGLETON(SceneManager);

public:
	bool Init(HWND hwnd);
	void Cleanup();

	void Process();

	void LoadLobbyData(const std::vector<IMAGE_DATA*> images);

	HDC GetBackDC() const { return _backDC; }

private:
	HWND _hwnd = nullptr;
	HDC _hDC = nullptr;
	HDC _memDC = nullptr;
	HDC _backDC = nullptr;
	HBITMAP _oldBitmap = nullptr;

	SCENE_TYPE _sceneType = SCENE_TYPE::Lobby;

	LobbyScene* _lobbyScene = nullptr;
	InGameScene* _inGameScene = nullptr;
};

