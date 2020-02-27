#pragma once
#include <wrl.h>
#include <d3d9.h>
#include "Math.h"
#include "Depth.h"


namespace Renderer
{
bool Initialize();
void Release();
LPDIRECT3DDEVICE9 GetDevice();
void DrawSprite(const RectF& rect, Depth* depth, const RectF& texCoords);
void SetTexture(Microsoft::WRL::ComPtr<IDirect3DTexture9> texture);
Vector2 GetSize();
}

