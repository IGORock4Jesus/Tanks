#pragma once
#include <wrl.h>
#include <d3d9.h>
#include "Math.h"


namespace Renderer
{
bool Initialize();
void Release();
LPDIRECT3DDEVICE9 GetDevice();
void DrawSprite(const Vector2& position, float depth, const Vector2& size, const RectF& rect);
void SetTexture(Microsoft::WRL::ComPtr<IDirect3DTexture9> texture);
Vector2 GetSize();
}

