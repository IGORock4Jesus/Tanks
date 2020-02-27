#pragma once

#include <map>
#include "Component.h"

namespace ECS
{
struct EntityAlreadyHasComponent : std::exception {};

class ComponentContainer {
public:
	virtual ~ComponentContainer()
	{
	}
};

template <typename _Component>
class TComponentContainer : public ComponentContainer {
	static_assert(std::is_base_of_v<Component, _Component>, "Тип _Component должен наследоваться от Component (TComponent)");

	const size_t size;
	size_t count;
	std::map<Entity*, _Component> components;
	static const ComponentID componentID;

public:
	TComponentContainer(size_t size)
		: size(size) {
	}

	_Component* Create(Entity* entity) {
		if (components.contains(entity))
			throw EntityAlreadyHasComponent;
		components.insert({ entity, _Component() });
		return &components[entity];
	}
};
}