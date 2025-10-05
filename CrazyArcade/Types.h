#pragma once

const UINT SCREEN_WIDTH = 800;
const UINT SCREEN_HEIGHT = 600;
const UINT MAP_WIDTH_SIZE = 15;
const UINT MAP_HEIGHT_SIZE = 11;
const UINT PLAYER_NUM = 2;

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
	int cols;
	int rows;
};

struct CHARACTER_STAT
{
	int bombNum;
	int bombLength;
	int speed;
	int bombNumMax;
	int bombLengthMax;
	int speedMax;
};

struct MAP_DATA
{
	std::string name;
	std::string path;
	int data[MAP_HEIGHT_SIZE][MAP_WIDTH_SIZE];
};

struct SELECT_DATA
{
	int redCharacter;
	int blueCharacter;
	int mapIndex;
};

enum class SCENE_TYPE
{
	Lobby,
	Loading,
	InGame,
	Existing,
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

enum class MAP_ENTITY
{
	Empty,
	Block,
	Wall,
	WaterBomb,
	Item
};

enum class BGM
{
	Room,
	Patrit,
};

enum class EFFECT_SOUND
{
	Install,
	Explosion,
	OverlappedButton,
	PickupItem,
	ExplodeCharacter,
};

enum class TEAM_COLOR
{
	None,
	Red,
	Blue,
};

enum class CHARACTER_NAME
{
	Bazzi,
	Dizni,
};

enum class CHARACTER_STATE
{
	Normal,
};

enum class DIRECTION
{
	Center,
	Left,
	Right,
	Up,
	Down,
};



