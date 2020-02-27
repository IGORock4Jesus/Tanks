#include "ComponentContainer.h"

namespace ECS {
template <typename _Component>
const ComponentID TComponentContainer<_Component>::componentID = GetComponentID<_Component>();
}