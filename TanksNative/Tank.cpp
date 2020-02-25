#include "Tank.h"
#include "exceptions.h"
#include "LevelConstructor.h"
#include "Scene.h"
#include "AnimationManager.h"
#include "GameObjectManager.h"


void Tank::OnLevelChanged(TankLevel level)
{
	if (controller)
		controller->GetTexture(this);
}

void Tank::OnDirectionChanged(Direction direction)
{
	if (controller)
		controller->GetTexture(this);
}

void Tank::XChanged(float newX)
{
	SetPosition({ newX, GetPosition().y });
}

void Tank::YChanged(float newY)
{
	SetPosition({ GetPosition().x, newY });
}

void Tank::Bullet_Destroyed(std::shared_ptr<GameObject>& gameObject)
{
	bullet = nullptr;
}

Tank::Tank(std::shared_ptr<ITankController> controller, TankType type, TankLevel level)
	:controller{ controller }, _Type{ type }, _Level{ level }, _Direction{ Direction::Top }
{
	if (!controller)
		throw ArgumentNullException("controller");

	controller->GetTexture(this);
}

void Tank::Step(Direction direction)
{
	float speed = 0.1f;

	// если направление не совпадает - меняем
	if (direction != _Direction)
	{
		SetDirection(direction);
	}
	// иначе двигаемся
	else
	{
		// вычисляем в каком мы квадранте
		int x = (int)round(GetPosition().x / LevelConstructor::GetMinBlockSize());
		int y = (int)round(GetPosition().y / LevelConstructor::GetMinBlockSize());

		// переходим на следующий, в зависимости от направления
		if (_Direction == Direction::Top)
		{
			if (y > 0)
				y--;
		}
		else if (_Direction == Direction::Bottom)
		{
			if (y < LevelConstructor::GetMinBlockCount() - 4)
				y++;
		}
		else if (_Direction == Direction::Left)
		{
			if (x > 0)
				x--;
		}
		else if (_Direction == Direction::Right)
		{
			if (x < LevelConstructor::GetMinBlockCount() - 4)
				x++;
		}

		auto xAnim = std::make_shared<AnimationManager::Animation>();
		xAnim->length = speed;
		xAnim->callback.Add(this, &Tank::XChanged);
		xAnim->frames.insert({ 0.0f, GetPosition().x });
		xAnim->frames.insert({ speed, x * LevelConstructor::GetMinBlockSize() });

		AnimationManager::Add(xAnim);

		auto yAnim = std::make_shared<AnimationManager::Animation>();
		yAnim->length = speed;
		yAnim->callback.Add(this, &Tank::YChanged);
		yAnim->frames.insert({ 0.0f, GetPosition().y });
		yAnim->frames.insert({ speed, y * LevelConstructor::GetMinBlockSize() });

		AnimationManager::Add(yAnim);
	}
}

void Tank::Shot()
{
	if (bullet)
		return;

	auto b = std::make_shared<Bullet>(_Direction);
	auto pos = GetPosition();

	if (_Direction == Direction::Top)
		pos += {GetSize().x / 2.0f - b->GetSize().x / 2.0f, -b->GetSize().y};
	else if (_Direction == Direction::Bottom)
		pos += {GetSize().x / 2.0f - b->GetSize().x / 2.0f, GetSize().y};
	else if (_Direction == Direction::Left)
		pos += {-b->GetSize().x, GetSize().y / 2.0f - b->GetSize().y / 2.0f};
	else if (_Direction == Direction::Right)
		pos += {GetSize().x, GetSize().y / 2.0f - b->GetSize().y / 2.0f};

	b->SetPosition(pos);

	bullet = b;
	Scene::Add(bullet);
	GameObjectManager::GetNode(b)->Destroyed.Add(this, &Tank::Bullet_Destroyed);
}

void Tank::Update(float elapsedTime)
{
	controller->Update(this, elapsedTime);
}
