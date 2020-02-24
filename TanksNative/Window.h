#pragma once

#include <Windows.h>


namespace Window
{
bool Initialize(HINSTANCE hinstance, int width, int height);
void Run();
HWND GetHandle();
}

