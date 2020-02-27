#pragma once

#include <map>

#include "Component.h"
#include "ComponentContainer.h"

namespace ECS
{
class ComponentManager {
	std::multimap<ComponentID, ComponentContainer*> containers;

public:
	~ComponentManager()
	{
		for (auto& container : containers) {
			delete container.second;
		}
	}

	// Регистрирует класс компонента
	template <typename _Component>
	void Register(size_t maxSize) {
		static_assert(std::is_base_of_v<Component, _Component>, "Конмпонент должен быть наследован от класса Component, точнее от его реализации TComponent.");
		containers.insert({ GetComponentID<_Component>(), new TComponentContainer<_Component>(maxSize) });
	}

	/*template <typename T>
	T> Create(Entity* entity) {
		static_assert(std::is_base_of_v<Component, T>, "Конмпонент должен быть наследован от класса Component, точнее от его реализации TComponent.");
		std::shared_ptr<T> component = std::make_shared<T>();
		component->Initialize(entity);
		components.push_back(component);
		return components;
	}*/

	/*template <typename T>
	std::shared_ptr<T> Get(Entity* entity) {
		static_assert(std::is_base_of_v<Component, T>, "Конмпонент должен быть наследован от класса Component, точнее от его реализации TComponent.");
		for (auto& c : components) {
			if (c->GetEntity() == entity) {
			}
		}
	}*/
};
}