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
}

void ImageManager::LoadImageDataFromTextFile(const std::string& path, std::vector<IMAGE_DATA*>& data)
{ 
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
			MessageQueue::StringToEnum(str[0]),
			(HBITMAP)LoadImage(nullptr, Utils::ToWString(str[1]).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION),
			stoi(str[2]),
			stoi(str[3]),
			stoi(str[4]),
			stoi(str[5]),
			stoi(str[6]),
			}
		);
	}

	fin.close();
}
