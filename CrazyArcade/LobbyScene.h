#pragma once

class Entity;

class LobbyScene
{
public:
	void LoadData(const std::vector<IMAGE_DATA*> images);

	void Process(HDC dc);

private:
	int _mapNum = 0;

	std::list<Entity*> _entities;
};

