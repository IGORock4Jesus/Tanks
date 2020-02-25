#pragma once

#include <memory>
#include "GameObject.h"


namespace GameObjectManager
{
constexpr size_t COUNT = 1024;

struct Node
{
	//std::atomic_bool enabled{ false };
	std::shared_ptr<GameObject> gameObject;
	Event<std::shared_ptr<GameObject>&> Destroyed;
	Event<std::shared_ptr<GameObject>&, std::shared_ptr<GameObject>&> CollisionDetected;
};

extern Node nodes[COUNT];

void Add(std::shared_ptr<GameObject> gameObject);
void Destroy(std::shared_ptr<GameObject> gameObject);
void Destroy(GameObject* const gameObject);
void Clear();
Node* GetNode(std::shared_ptr<GameObject> gameObject);

}

