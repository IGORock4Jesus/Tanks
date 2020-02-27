#pragma once

#include <list>
#include <memory>

#include "Component.h"

namespace ECS
{
class ComponentManager {
	std::list<std::shared_ptr<Component>> components;

public:
	template <typename T>
	std::shared_ptr<T> Create(Entity* entity) {
		static_assert(std::is_base_of_v<Component, T>, "Конмпонент должен быть наследован от класса Component, точнее от его реализации TComponent.");
		std::shared_ptr<T> component = std::make_shared<T>();
		component->Initialize(entity);
		components.push_back(component);
		return components;
	}

	template <typename T>
	std::shared_ptr<T> Get(Entity* entity) {
		static_assert(std::is_base_of_v<Component, T>, "Конмпонент должен быть наследован от класса Component, точнее от его реализации TComponent.");
		for (auto& c : components) {
			if (c->GetEntity() == entity) {
			}
		}
	}
};
}