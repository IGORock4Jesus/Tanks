#include "Component.h"

namespace ECS {
ComponentID uniqueID{ 0 };
constexpr ComponentID MakeUniqueComponentID() {
	return uniqueID++;
}
}