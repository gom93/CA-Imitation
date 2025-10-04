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
	void LoadInGameData(const std::vector<IMAGE_DATA*> images);
	void LoadCharacterData(const IMAGE_DATA** images, const CHARACTER_STAT* states);
	void LoadItemData(const std::vector<IMAGE_DATA*> images);
	void LoadMapData(const MAP_DATA& mapData);

	HDC			GetBackDC() const { return _backDC; }
	SCENE_TYPE	GetSceneType() const { return _sceneType; }
	void		SetSceneType(SCENE_TYPE type) { _sceneType = type; }
	
	const SELECT_DATA& GetSelectData() const { return _selectData; }

private:
	HWND			_hwnd = nullptr;
	HDC				_hDC = nullptr;
	HDC				_memDC = nullptr;
	HDC				_backDC = nullptr;
	HBITMAP			_oldBitmap = nullptr;

	SCENE_TYPE		_sceneType = SCENE_TYPE::Lobby;

	LobbyScene*		_lobbyScene = nullptr;
	InGameScene*	_inGameScene = nullptr;

	SELECT_DATA		_selectData = {};
};

