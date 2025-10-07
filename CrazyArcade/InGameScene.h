#pragma once

class Entity;
class Character;
class WaterBomb;

class InGameScene
{
public:
	void LoadInGameData(const std::vector<IMAGE_DATA*> images);
	void LoadCharacterData(const IMAGE_DATA* characterImage, const IMAGE_DATA* trappedImage, const IMAGE_DATA* dieImage, const CHARACTER_STAT& characterStats);
	void LoadItemData(const std::vector<IMAGE_DATA*> images);
	void SetMapData(const MAP_DATA& mapData);
	void LoadStaticEntityData();

	void Process(HDC dc);

	const std::list<Entity*>& GetInGameEntities() const { return _inGameEntites; }

private:
	void DestroyHitEntity(const std::vector<VEC2>& hitPos);

	void CreateBomb(Character* character);
	void DestroyBombs();

	static bool EraseBomb(Entity* entity);
	static bool SortEntity(Entity* a, Entity* b);

private:
	std::list<Entity*>		_allEntities;
	std::list<Entity*>		_inGameEntites;
	std::list<Character*>	_characters;
	std::list<WaterBomb*>	_waterBombs;

	/* 0: Block, 1: Wall, 2: WaterBomb */
	std::vector<IMAGE_DATA*> _entityDatas;	
	std::vector<BITMAP>		 _entityBitmap;
	bool					_isExplosion = false;

	MAP_DATA				_mapData = {};

	static VEC2				_eraseBombPos;
};

