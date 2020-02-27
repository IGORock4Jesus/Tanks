#pragma once

namespace ECS {
struct Entity;
using ComponentID = size_t;

class Component {
	Entity* entity;
	const ComponentID id;
public:
	Component(ComponentID id)
		: id{ id } {}

	void Initialize(Entity* entity) {
		this->entity = entity;
		OnInitialized();
	}
	virtual void OnInitialized() {}
	inline const Entity* GetEntity() const { return entity; }
};

ComponentID MakeUniqueComponentID();

template <typename T>
ComponentID GetComponentID() {
	static ComponentID id = MakeUniqueComponentID();
	return id;
}

template <typename T>
class TComponent :public Component {
};
}