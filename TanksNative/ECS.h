#pragma once

#include <string>
#include "Property.h"

namespace ECS {

// ��������
class Entity {
	PROPERTY(std::wstring, name);//���
};

constexpr size_t MAX_ENTITY_COUNT = 1024;//����������� ���������� ���������
using EntityID = size_t; // ������������� ��������
constexpr EntityID FAILED_ENTITY_ID = (-1); // ������������ ������������� ��������
using ComponentID = size_t; // ������������� ���� ����������
constexpr ComponentID FAILED_COMPONENT_ID = (-1); // ������������ ������������� ���� ����������

// ������� ����� �����������.
// ������ �� ���� �������������.
// ��� ������������ ����������� ��������� ����� TComponent
class Component {
public:
	virtual ComponentID GetComponentID() const = 0;
	virtual void Update(EntityID entityID, float elapsedTime) {}
	virtual void Render(EntityID entityID) {}
	virtual void Initialize(ECS::EntityID entityID) {}
};

// ������� ���������� ������������� ����������
constexpr ComponentID MakeUniqueComponentID();

// ���������� ������������� ���������� T
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