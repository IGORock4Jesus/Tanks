#include "LevelConstructor.h"
#include <string>
#include <map>
#include <memory>

#include "Renderer.h"
#include "Scene.h"

#include "Flag.h"
#include "Tank.h"
#include "UserTankController.h"
#include "Walls.h"
#include "Block.h"


namespace LevelConstructor {
float blockSize;
size_t minBlockCount;
float minBlockSize;
std::map<char, Walls> constructors{
	std::make_pair('.', Walls::Unknown),
	std::make_pair('#', Walls::Brick_Whole),
	std::make_pair('@', Walls::Concrete),					 						
	std::make_pair('%', Walls::Forest),
	std::make_pair('~', Walls::Water_1),
	std::make_pair('-', Walls::Ice)
		};


void Construct(std::shared_ptr<Level> level) {
	auto screenSize = Renderer::GetSize();

	Scene::Clear();

	blockSize = min(screenSize.x, screenSize.y) / LevelSize;

	minBlockCount = LevelSize * 2;
	minBlockSize = blockSize / 2.0f;

	for (int y = 0; y < LevelSize; y++)
	{
		for (int x = 0; x < LevelSize; x++)
		{
			if (constructors.contains(level->blocks[x][y]) == false)
				throw std::exception((std::string("Конструктор уравня для элемента '") + level->blocks[x][y] + "' - не реализован!").c_str());

			auto& constructor = constructors[level->blocks[x][y]];
			auto block = std::make_shared<Block>(constructor);
			if (!block)
				continue;

			block->SetPosition({ x * blockSize, y * blockSize });
			block->SetSize({ blockSize, blockSize });

			Scene::Add(block);
		}
	}

	// add flag
	auto flag = std::make_shared<Flag>();
	flag->SetPosition({ 12 * blockSize, 24 * blockSize });
	flag->SetDepth(&Depth::Action);
	flag->SetSize(Vector2{ blockSize, blockSize } *2.0f);

	Scene::Add(flag);

	// demo: add user tank
	auto userTank = std::make_shared< Tank>(std::make_shared<UserTankController>(), TankType::Enemy_1, TankLevel::Fast);
	userTank->SetPosition({ 8 * blockSize, 24 * blockSize }),
		userTank->SetSize(Vector2{ blockSize, blockSize } *2.0f);
	userTank->SetDepth(&Depth::Action);
	userTank->SetDirection(Direction::Top);

	Scene::Add(userTank);
}

float GetBlockSize()
{
	return blockSize;
}

size_t GetMinBlockCount()
{
	return minBlockCount;
}

float GetMinBlockSize()
{
	return minBlockSize;
}

}