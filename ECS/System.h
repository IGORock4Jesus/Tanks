#pragma once

#include "Component.h"

namespace ECS {
class System {
};

template <typename ..._Components>
class TSystem : public System {
};
}