#include "pch.h"
#include "MapManager.h"

void MapManager::LoadMapDataFromFile()
{
	std::ifstream fin("Data/MapData.txt");
	std::string str[2];
	for (UINT i = 0; i < 2; i++)
	{
		getline(fin, str[0]);
	}

	while (!fin.eof())
	{
		for (UINT i = 0; i < 2; i++)
		{
			fin >> str[i];
		}

		_mapData.emplace_back(MAP_DATA{
			str[0],								// 맵 이름
			str[1],								// 파일 경로
			0									// 맵 데이터
			});
	}
	fin.close();
}

const MAP_DATA& MapManager::LoadMap(const SELECT_DATA& selectData)
{
	std::ifstream fin(_mapData[selectData.mapIndex].path);
	int cols = 0;
	int rows = 0;

	char c;
	while (!fin.eof())
	{
		fin.get(c);
		if (c == '\n')
		{
			rows++;
			cols = 0;
		}
		else
		{
			_mapData[selectData.mapIndex].data[rows][cols++] = c - '0';
		}
	}

	fin.close();

	return _mapData[selectData.mapIndex];
}
