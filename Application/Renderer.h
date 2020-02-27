#pragma once

#include "APPLICATION_API.h"
#include "IApplicationLayer.h"
#include "Event.h"
#include "Window.h"
#include <Mathematics/RectF.h>

class RendererImpl;
class APPLICATION_API Renderer : public IApplicationLayer
{
	RendererImpl* impl;
	size_t width, height;

public:
	Event<Renderer*> Rendering;

	Renderer(Window* window);
	~Renderer();

	// Унаследовано через IApplicationLayer
	virtual void Update() override;

	void DrawSprite(const RectF& rect, float depth, const RectF& texCoords);
	//void SetTexture();
};
