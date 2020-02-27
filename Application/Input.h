#pragma once

#include <dinput.h>
#include <string>

#include "APPLICATION_API.h"
#include "IApplicationLayer.h"
#include "Event.h"

class Input : public IApplicationLayer
{
	LPDIRECTINPUT8 direct;
	LPDIRECTINPUTDEVICE8 keyboard;
	char keyState[256];

public:
	Event<std::wstring> KeyDown, KeyUp;

	Input(HINSTANCE hinstance, HWND hwnd);
	~Input();

	// Унаследовано через IApplicationLayer
	virtual void Update() override;
};
