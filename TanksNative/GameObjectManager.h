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
};

extern Node nodes[COUNT];

void Add(std::shared_ptr<GameObject> gameObject);
void Destroy(std::shared_ptr<GameObject> gameObject);
void Clear();
}

