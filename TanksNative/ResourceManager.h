#pragma once
#include <memory>
#include <wrl.h>
#include <string>
#include "Level.h"
#include "Math.h"
#include "TankType.h"
#include "TankLevel.h"
#include "Direction.h"
#include "Walls.h"


namespace ResourceManager
{
bool LoadAll();
void Release();


Microsoft::WRL::ComPtr<IDirect3DTexture9> GetTexture();
std::shared_ptr<Level> GetLevel(std::wstring name);

RectF GetTankCoords(TankType type, Direction direction, TankLevel level, int frame);

RectF GetWallCoords(Walls wall);

RectF GetBulletCoords(Direction direction);

RectF GetFlagCoords();

}
