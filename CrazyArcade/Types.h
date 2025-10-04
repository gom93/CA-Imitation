#pragma once

const UINT SCREEN_WIDTH = 800;
const UINT SCREEN_HEIGHT = 600;

struct VEC2
{
	int x;
	int y;

	bool operator==(const VEC2 v)
	{
		if (x == v.x && y == v.y)
		{
			return true;
		}
		return false;
	}
};

struct IMAGE_DATA
{
	int id;
	HBITMAP bitmap;
	int type;
	int x;
	int y;
	int width;
	int height;
};

enum class SCENE_TYPE
{
	Lobby,
	InGame,
};

enum class ENTITY_TYPE
{
	Static,
	Dynamic,
	Button,
};

enum class ENTITY_INDEX
{
	Background,
	RedCharacter,
	BlueCharacter,
	BazziPickImage,
	DizniPickImage,
	RandomPickImage,
	Exit,
	Map,
	MapPick,
	Start,
	Block,
	Wall,
	WaterBallon,
	RedBazzi,
	RedDizni,
	BlueBazzi,
	BlueDizni,
	Trapped,
	Die,
	DrawUI,
	LoseUI,
	WinUI,
	BompUP,
	PowerUP,
	SpeedUP,
	None,
};




