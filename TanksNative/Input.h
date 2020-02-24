#pragma once

#include <string>
#include <Windows.h>

namespace Input
{
bool IskeyDown(std::wstring key);
bool Initialize(HINSTANCE hinstance);
void Release();
void Update();
};

