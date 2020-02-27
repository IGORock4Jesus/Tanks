#pragma once

#include <string>
#include <vector>

#include "ECS_API.h"
#include "Entity.h"

namespace ECS {
class ECS_API EntityManager {
	const size_t maxCount;
	struct Node
	{
		bool used;
		Entity entity;
	};
	std::vector<Node> entities;
	size_t count;

public:
	EntityManager(size_t maxCount);

	Entity* Create();
	void Remove(Entity* entity);
	const Entity* Get(const std::wstring& name) const;
	size_t Count() const;
};
}
