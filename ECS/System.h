#pragma once

#include "Component.h"

namespace ECS {
class System {
public:
	virtual void Update(float elapsedTime) {}
};

template <typename ..._Components>
class TSystem : public System {
};
}