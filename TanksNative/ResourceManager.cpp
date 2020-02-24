#include "ResourceManager.h"
#include <d3dx9.h>
#include <map>
#include <string>
#include <memory>
#include "Renderer.h"
#include <filesystem>
#include <fstream>

namespace ResourceManager
{
Microsoft::WRL::ComPtr<IDirect3DTexture9> texture;
SIZE textureSize{ 1216, 512 };
std::map<std::wstring, std::shared_ptr<Level>> levels;

std::shared_ptr<Level> LoadLevel(std::wstring filename) {
	std::shared_ptr<Level> level = std::make_shared<Level>();

	auto file = std::ifstream(filename);
	if (file.is_open()) {
		for (size_t y = 0; y < LevelSize; y++)
		{
			for (size_t x = 0; x < LevelSize; x++)
			{
				file >> level->blocks[x][y];
			}
		}
	}

	return level;
}

bool LoadAll() {
	if (FAILED(D3DXCreateTextureFromFile(Renderer::GetDevice(), L"..\\resources\\png\\texture.png", &texture)))
		return false;

	for (auto file : std::filesystem::directory_iterator("..\\resources\\levels\\"))
	{
		auto path = file.path().native();

		auto slashPos = path.find_last_of(L'\\');
		if (slashPos == std::wstring::npos)
			slashPos = 0;
		slashPos++;
		auto dotPos = path.find_last_of(L'.');
		if (dotPos == std::wstring::npos)
			dotPos = path.length();

		auto name = path.substr(slashPos, dotPos - slashPos);

		levels[name] = LoadLevel(path);
	}

	return true;
}
void Release() {
}
Microsoft::WRL::ComPtr<IDirect3DTexture9> GetTexture() {
	return texture;
}
std::shared_ptr<Level> GetLevel(std::wstring name) {
	return levels[name];
}

RectF Convert(const RectF& rectangle) {
	return {
		rectangle.x / textureSize.cx,
		rectangle.y / textureSize.cy,
		rectangle.width / textureSize.cx,
		rectangle.height / textureSize.cy
	};
}

RectF GetTankCoords(TankType type, Direction direction, TankLevel level, int frame)
{
	const int size = 32;
	int tankLevel = (int)level;
	tankLevel--;

	int typeIndex = (int)type;
	int dirIndex = (int)direction;

	RectF rectangle = {
		typeIndex * size * 4 + dirIndex * size,
		(int)tankLevel * size * 2 + frame * size,
		size, size
	};

	return Convert(rectangle);
}

RectF GetWallCoords(Walls wall)
{
	const int x = 928;
	const int size = 16;
	int y = size * (int)wall;
	return Convert({ (float)x, (float)y, (float)size, (float)size });
}

RectF GetBulletCoords(Direction direction)
{
	int startX = 944, startY = 128;
	int size = 8;

	return Convert({
			(float)startX + size * (int)direction,
			(float)startY,
			(float)size,
			(float)size
		});
}

RectF GetFlagCoords()
{
	return Convert({ (float)944, (float)0, (float)32, (float)32 });
}


}
