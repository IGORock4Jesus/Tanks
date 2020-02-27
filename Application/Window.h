#pragma once

#include <Windows.h>
#include "APPLICATION_API.h"
#include "IApplicationLayer.h"
#include "Event.h"

class APPLICATION_API Window : public IApplicationLayer
{
	HWND handle;
	LPCWSTR ClassName = L"TANK WINDOW";

	static LRESULT CALLBACK StaticProcedure(HWND h, UINT m, WPARAM w, LPARAM l);
	LRESULT Procedure(HWND h, UINT m, WPARAM w, LPARAM l);

public:
	Event<Window*> Closed;

	Window(HINSTANCE hinstance, int width, int height);

	HWND GetHandle() const { return handle; }

	// Унаследовано через IApplicationLayer
	virtual void Update() override;
};
