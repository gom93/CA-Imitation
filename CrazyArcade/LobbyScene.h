#pragma once

class Entity;

class LobbyScene
{
public:
	void LoadData(const std::vector<IMAGE_DATA*> images);

	void Process(HDC dc);

	const std::list<Entity*>& GetEntities() const { return _entities; }

private:
	int _mapNum = 0;

	std::list<Entity*> _entities;
};

