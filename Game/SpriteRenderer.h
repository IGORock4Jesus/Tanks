#pragma once

#include <ECS/System.h>
#include "BoundsComponent.h"

class SpriteRenderer : public ECS::TSystem<BoundsComponent>
{
};
