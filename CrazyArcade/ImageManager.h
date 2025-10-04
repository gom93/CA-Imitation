#pragma once

class ImageManager
{
	DECLARE_SINGLETON(ImageManager);

public:
	void Cleanup();

	void LoadImageData();

	const std::vector<IMAGE_DATA*>& GetLobbyImages() { return _lobbyImages; }

private:
	void LoadImageDataFromTextFile(const std::string& path, std::vector<IMAGE_DATA*>& data);

private:
	static const UINT IMAGE_DATA_COLUMN = 7;
	
	std::vector<IMAGE_DATA*> _lobbyImages = {};
};

