#pragma once

#include <ECS/Component.h>
#include <Mathematics/RectF.h>

struct TextureComponent : ECS::TComponent<TextureComponent>
{
	RectF textureCoords;
};