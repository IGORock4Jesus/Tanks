#pragma once
#include <memory>
#include "Level.h"


namespace LevelConstructor {

void Construct(std::shared_ptr<Level> level);
float GetBlockSize();
size_t GetMinBlockCount();
float GetMinBlockSize();

}