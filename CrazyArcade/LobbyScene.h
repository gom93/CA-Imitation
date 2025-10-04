#pragma once

class Entity;

class LobbyScene
{
public:
	void				LoadData(const std::vector<IMAGE_DATA*> images);

	void				Process(HDC dc);

	void				SaveSelectData();
	const SELECT_DATA&  GetSelectData() const;

	const std::list<Entity*>& GetEntities() const { return _entities; }
	

private:
	int _mapNum = 0;

	SELECT_DATA _selectData = {};

	std::list<Entity*> _entities;
};

