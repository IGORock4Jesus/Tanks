#include "Bullet.h"
#include "LevelConstructor.h"
#include "ResourceManager.h"
#include "Log.h"
#include "Block.h"


Bullet::Bullet(Direction direction)
	: direction{ direction }, _Speed{ &BulletSpeed::Normal }
{
	SetSize({ LevelConstructor::GetMinBlockSize(),
		LevelConstructor::GetMinBlockSize() });
	SetTextureCoords(ResourceManager::GetBulletCoords(direction));
}

void Bullet::Update(float elapsedTime)
{
	// перемещаемся
	float units = (_Speed->GetValue()) * elapsedTime;
	if (direction == Direction::Top)
		SetPosition({ GetPosition().x, GetPosition().y - units });
	else if (direction == Direction::Bottom)
		SetPosition({ GetPosition().x, GetPosition().y + units });
	else if (direction == Direction::Right)
		SetPosition({ GetPosition().x + units, GetPosition().y });
	else if (direction == Direction::Left)
		SetPosition({ GetPosition().x - units, GetPosition().y });
}

void Bullet::OnCollisionDetected(std::shared_ptr<GameObject>& another)
{
	auto block = std::dynamic_pointer_cast<Block>(another);
	if (block) {
		Log::WriteLine(L"Bullet is crushed!");
		block->
	}
}
