#include "Block.h"
#include "ResourceManager.h"


Block::Block(Walls wall)
    : _Wall{ wall }
{
    SetTextureCoords(ResourceManager::GetWallCoords(wall));

	switch (wall)
	{
    case Walls::Brick_Whole:
    case Walls::Brick_Top:
    case Walls::Brick_Right:
    case Walls::Brick_Bottom:
    case Walls::Brick_Left:
    case Walls::Brick_RightTop:
    case Walls::Brick_RightBottom:
    case Walls::Brick_LeftTop:
    case Walls::Brick_LeftBottom:
    case Walls::Concrete:
        SetDepth(&Depth::Action);
        break;
    case Walls::Water_1:
    case Walls::Water_2:
    case Walls::Ice:
        SetDepth(&Depth::Ground);
        break;
    case Walls::Forest:
        SetDepth(&Depth::Covers);
        break;
    case Walls::Unknown:
        break;
    default:
        break;
	}
}
