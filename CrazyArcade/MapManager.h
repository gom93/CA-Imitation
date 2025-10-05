#pragma once

class MapManager
{
	DECLARE_SINGLETON(MapManager);

public:
	void LoadMapDataFromFile();
	const MAP_DATA& LoadMap(const SELECT_DATA& selectData);

private:
	std::vector<MAP_DATA> _mapData = {};
};

