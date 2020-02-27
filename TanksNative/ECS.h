#pragma once

#include <string>
#include "Property.h"

namespace ECS {

// сущность
class Entity {
	PROPERTY(std::wstring, name);//имя
};

constexpr size_t MAX_ENTITY_COUNT = 1024;//масимальное количество сущностей
using EntityID = size_t; // идентификатор сущности
constexpr EntityID FAILED_ENTITY_ID = (-1); // неправильный идентификатор сущности
using ComponentID = size_t; // идентификатор типа компонента
constexpr ComponentID FAILED_COMPONENT_ID = (-1); // неправильный идентификатор типа компонента

// базовый класс компонентов.
// Нельзя от него наследоваться.
// Для наследования используйте шаблонный класс TComponent
class Component {
public:
	virtual ComponentID GetComponentID() const = 0;
	virtual void Update(EntityID entityID, float elapsedTime) {}
	virtual void Render(EntityID entityID) {}
	virtual void Initialize(ECS::EntityID entityID) {}
};

// создает уникальный идентификатор компонента
constexpr ComponentID MakeUniqueComponentID();

// возвращает идентификатор компонента T
template <typename T>
ComponentID GetComponentID() {
	static ComponentID componentID = MakeUniqueComponentID();
	return componentID;
}

template <typename T>
struct TComponent : Component {
	constexpr ComponentID componentID = GetComponentID<T>();
	virtual ComponentID GetComponentID() const override { return componentID; }
	static T buffer[MAX_ENTITY_COUNT];
};

EntityID CreateEntity();
void Clear();

template <typename T>
void Register();

template <typename T>
T* CreateComponent(EntityID entityID);
template <typename T>
void Reset(EntityID entityID);
template <typename T>
T&& Get(EntityID entityID);

void Update(float elaspedTime);
void Render();

}