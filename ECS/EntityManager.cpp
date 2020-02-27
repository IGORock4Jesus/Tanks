#include "EntityManager.h"
#include "InvalidCallException.h"
#include "ArgumentNullException.h"
#include "ArgumentException.h"

namespace ECS
{
EntityManager::EntityManager(size_t maxCount)
	: maxCount{ maxCount }, count{ 0ULL }
{
	entities.resize(maxCount);
}

Entity* EntityManager::Create()
{
	for (auto& node : entities) {
		if (node.used)
			continue;

		node.used = true;
		count++;
		return &node.entity;
	}
	throw InvalidCallException("Не хватает места для новой сущности.");
}

void EntityManager::Remove(Entity* entity)
{
	if (!entity)
		throw ArgumentNullException("entity");

	for (auto& node : entities) {
		if (&node.entity == entity) {
			node.used = false;
			count--;
			return;
		}
	}

	throw ArgumentExcpection("entity");
}

size_t EntityManager::Count() const
{
	return count;
}

const Entity* EntityManager::Get(const std::wstring& name) const
{
	for (auto& node : entities) {
		if (node.used && node.entity.name == name) {
			return &node.entity;
		}
	}
	return nullptr;
}
}