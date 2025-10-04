#pragma once

class Character;

class InGameScene
{
public:
	void LoadInGameData(const std::vector<IMAGE_DATA*> images);
	void LoadCharacterData(const IMAGE_DATA* characterImage, const IMAGE_DATA* trappedImage, const IMAGE_DATA* dieImage, const CHARACTER_STAT& characterStats);
	void LoadItemData(const std::vector<IMAGE_DATA*> images);
	void LoadMapData(const MAP_DATA& mapData);

	void Process(HDC dc);

	const std::list<Entity*>& GetEntities() const { return _entities; }

private:
	std::list<Entity*>		_entities;
	std::list<Character*>	_characters;
};

