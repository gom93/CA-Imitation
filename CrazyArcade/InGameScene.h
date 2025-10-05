#pragma once

class Character;
class WaterBomb;

class InGameScene
{
public:
	void LoadInGameData(const std::vector<IMAGE_DATA*> images);
	void LoadCharacterData(const IMAGE_DATA* characterImage, const IMAGE_DATA* trappedImage, const IMAGE_DATA* dieImage, const CHARACTER_STAT& characterStats);
	void LoadItemData(const std::vector<IMAGE_DATA*> images);
	void LoadMapData(const MAP_DATA& mapData);

	void Process(HDC dc);

	const std::list<Entity*>& GetInGameEntities() const { return _inGameEntites; }

private:
	void CreateBomb(Character* character);

private:
	std::list<Entity*>		_allEntites;
	std::list<Entity*>		_inGameEntites;
	std::list<Character*>	_characters;
	std::list<WaterBomb*>	_waterBombs;

	/* 0: Block, 1: Wall, 2: WaterBomb */
	std::vector<IMAGE_DATA*> _entityDatas;	
	std::vector<BITMAP>		 _entityBitmap;
};

