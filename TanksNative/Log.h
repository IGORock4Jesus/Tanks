#pragma once

#include <string>
#include <Windows.h>

namespace Log
{
inline void WriteLine(std::wstring text) {
	OutputDebugString((text + L"\r\n").c_str());
}
}

