#include "pch.h"
#include "ImageManager.h"

void ImageManager::Cleanup()
{
	for (const IMAGE_DATA* image : _lobbyImages)
	{
		delete image;
	}
	_lobbyImages.clear();
}

void ImageManager::LoadImageData()
{
	LoadImageDataFromTextFile("Data/LobbyImageData.txt", _lobbyImages);
	LoadImageDataFromTextFile("Data/InGameImageData.txt", _inGameImages);
	LoadImageDataFromTextFile("Data/CharacterImageData.txt", _characterImages);
	LoadStateDataFromTextFile("Data/CharacterStatsData.txt", _characterStats);
	LoadImageDataFromTextFile("Data/items.txt", _items);
}

const IMAGE_DATA** ImageManager::GetCharacterImage(const SELECT_DATA& selectData)
{
	switch ((CHARACTER_SELECT_TYPE)selectData.redCharacter)
	{
	case CHARACTER_SELECT_TYPE::Bazzi:
		_characters[0] = _characterImages[0];
		break;
	case CHARACTER_SELECT_TYPE::Dizni:
		_characters[0] = _characterImages[1];
		break;
	default:
		// @TODO:
		break;
	}

	switch ((CHARACTER_SELECT_TYPE)selectData.blueCharacter)
	{
	case CHARACTER_SELECT_TYPE::Bazzi:
		_characters[1] = _characterImages[2];
		break;
	case CHARACTER_SELECT_TYPE::Dizni:
		_characters[1] = _characterImages[3];
		break;
	default:
		// @TODO:
		break;
	}

	// Trapped
	_characters[2] = _characterImages[4];

	// Die
	_characters[3] = _characterImages[5];

	return _characters;
}

const CHARACTER_STAT* ImageManager::GetCharacterStats(const SELECT_DATA& selectData)
{
	switch ((CHARACTER_SELECT_TYPE)selectData.redCharacter)
	{
	case CHARACTER_SELECT_TYPE::Bazzi:
		_stats[0] = _characterStats[0];
		break;
	case CHARACTER_SELECT_TYPE::Dizni:
		_stats[0] = _characterStats[1];
		break;
	default:
		// @TODO:
		break;
	}

	switch ((CHARACTER_SELECT_TYPE)selectData.blueCharacter)
	{
	case CHARACTER_SELECT_TYPE::Bazzi:
		_stats[1] = _characterStats[0];
		break;
	case CHARACTER_SELECT_TYPE::Dizni:
		_stats[1] = _characterStats[1];
		break;
	default:
		// @TODO:
		break;
	}

	return _stats;
}

void ImageManager::LoadImageDataFromTextFile(const std::string& path, std::vector<IMAGE_DATA*>& data)
{
	// ���� �κ� ���� �б�
	std::ifstream fin(path);
	std::string str[IMAGE_DATA_COLUMN];
	for (UINT i = 0; i < 2; i++)
	{
		getline(fin, str[0]);
	}

	while (!fin.eof())
	{
		for (UINT i = 0; i < IMAGE_DATA_COLUMN; i++)
		{
			fin >> str[i];
		}

		data.emplace_back(new IMAGE_DATA{
			MessageQueue::StringToEnum(str[0]),																							// Entity Index
			(HBITMAP)LoadImage(nullptr, Utils::ToWString(str[1]).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION),	// Bitmap
			stoi(str[2]),																												// Entity Type
			stoi(str[3]),																												// x ��ǥ
			stoi(str[4]),																												// y ��ǥ
			stoi(str[5]),																												// �̹��� �� ����
			stoi(str[6]),																												// �̹��� �� ����
			});
	}

	fin.close();
}

void ImageManager::LoadStateDataFromTextFile(const std::string& path, std::vector<CHARACTER_STAT>& data)
{
	// ���� �κ� ���� �б�
	std::ifstream fin(path);
	std::string str[IMAGE_DATA_COLUMN];
	for (UINT i = 0; i < 2; i++)
	{
		getline(fin, str[0]);
	}

	while (!fin.eof())
	{
		for (UINT i = 0; i < IMAGE_DATA_COLUMN; i++)
		{
			fin >> str[i];
		}

		data.emplace_back(CHARACTER_STAT{ // str[0] �� �̸� => �ش� �κп��� ������ ����
			stoi(str[1]),					   // �ʱ� ǳ�� ����
			stoi(str[2]),					   // �ʱ� ǳ�� ����
			stoi(str[3]),					   // �ʱ� ĳ���� �̵��ӵ�
			stoi(str[4]),					   // �ִ� ǳ�� ����
			stoi(str[5]),					   // �ִ� ǳ�� ����
			stoi(str[6])					   // �ִ� ĳ���� �̵��ӵ�
			});
	}

	fin.close();
}
