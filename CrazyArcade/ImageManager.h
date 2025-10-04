#pragma once

class ImageManager
{
	DECLARE_SINGLETON(ImageManager);

public:
	void Cleanup();

	void LoadImageData();

	const std::vector<IMAGE_DATA*>& GetLobbyImages() const { return _lobbyImages; }
	const std::vector<IMAGE_DATA*>& GetInGameImages() const { return _inGameImages; }
	const IMAGE_DATA**				GetCharacterImage(const SELECT_DATA& selectData);
	const CHARACTER_STAT*			GetCharacterStats(const SELECT_DATA& selectData);

private:
	void LoadImageDataFromTextFile(const std::string& path, std::vector<IMAGE_DATA*>& data);
	void LoadStateDataFromTextFile(const std::string& path, std::vector<CHARACTER_STAT>& data);

private:
	static const UINT IMAGE_DATA_COLUMN = 7;
	
	std::vector<IMAGE_DATA*>		_lobbyImages = {};
	std::vector<IMAGE_DATA*>		_inGameImages = {};
	std::vector<IMAGE_DATA*>		_characterImages = {};
	std::vector<CHARACTER_STAT>		_characterStats = {};
	std::vector<IMAGE_DATA*>		_items = {};
	
	const IMAGE_DATA*				_characters[PLAYER_NUM + 2] = {};						// +2 : Trapped, Die 이미지 데이터 저장 시 필요
	CHARACTER_STAT					_stats[PLAYER_NUM] = {};
};

