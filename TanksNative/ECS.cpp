#include "ECS.h"
#include <map>
#include <vector>


namespace ECS {

template <typename T>
struct TNode {
	bool used{ false };
	T object;
};

template <typename T>
TNode<T>* EnableNode(TNode<T>* nodes) {
	for (size_t i = 0; i < MAX_ENTITY_COUNT; i++)
	{
		if (nodes[i].used == false) {
			nodes[i].used = true;
			return &nodes[i];
		}
	}
	return nullptr;
}

TNode<Entity> entities[MAX_ENTITY_COUNT];
//std::map<ComponentID, std::vector<TNode<T>>> components;


ComponentID id{ 0 };
constexpr ComponentID MakeUniqueComponentID()
{
	return id++;
}

EntityID CreateEntity() {
	for (size_t i = 0; i < MAX_ENTITY_COUNT; i++)
	{
		if (entities[i].used == false) {
			entities[i].used = true;
			return i;
		}
	}
	return FAILED_ENTITY_ID;
}

void Clear()
{
	for (size_t i = 0; i < MAX_ENTITY_COUNT; i++)
	{
		if (entities[i].used) {
			entities[i].used = false;
		}
	}
}

void Update(float elaspedTime)
{
	for (size_t i = 0; i < MAX_ENTITY_COUNT; i++)
	{
		if (entities[i].used) {
			auto& m = components[i];
			for (auto& c : m) {
				c.object.Update(i, elaspedTime);
			}
		}
	}
}

void Render()
{
	for (size_t i = 0; i < MAX_ENTITY_COUNT; i++)
	{
		if (entities[i].used) {
			auto& m = components[i];
			for (auto& c : m) {
				c.object.Render(i);
			}
		}
	}
}

template<typename T>
void Register()
{
	std::vector<TNode<T>> nodes;
	nodes.resize(MAX_ENTITY_COUNT);
	components[GetComponentID<T>()] = std::move(nodes);
}

template <typename T>
T* CreateComponent(EntityID entityID) {
	auto& c = components[GetComponentID<T>()][entityID];
	c.used = true;
	c.object.Initialize(entityID);
	return &c;
}

template <typename T>
void Reset(EntityID entityID) {
	auto& c = components[GetComponentID<T>()][entityID];
	c.used = false;
}
template <typename T>
T&& Get(EntityID entityID) {
	auto& c = components[GetComponentID<T>()][entityID];
	return c.object;
}

}