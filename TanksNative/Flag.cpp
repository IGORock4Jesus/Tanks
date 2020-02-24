#include "Flag.h"
#include "ResourceManager.h"


Flag::Flag()
{
	SetTextureCoords(ResourceManager::GetFlagCoords());
}
