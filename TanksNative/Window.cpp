#include "Window.h"


namespace Window
{
HWND handle;
LPCWSTR ClassName = L"TANK WINDOW";

LRESULT CALLBACK Procedure(HWND h, UINT m, WPARAM w, LPARAM l) {
	switch (m)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(h, m, w, l);
	}
}

bool Initialize(HINSTANCE hinstance, int width, int height) {
	WNDCLASS wc{ 0 };
	wc.lpfnWndProc = Procedure;
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hinstance;
	wc.lpszClassName = ClassName;
	RegisterClass(&wc);
	int sw = ::GetSystemMetrics(SM_CXSCREEN);
	int sh = ::GetSystemMetrics(SM_CYSCREEN);
	RECT rect{ sw / 2 - width / 2, sh / 2 - height / 2, sw / 2 + width / 2, sh / 2 + height / 2 };
	::AdjustWindowRect(&rect, WS_POPUPWINDOW, FALSE);
	handle = ::CreateWindow(ClassName, ClassName, WS_POPUPWINDOW, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, HWND_DESKTOP, nullptr, hinstance, nullptr);
	if (!handle)
		return false;
	ShowWindow(handle, SW_NORMAL);
	UpdateWindow(handle);
	return true;
}

void Run() {
	MSG msg;
	while (::GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

HWND GetHandle()
{
	return handle;
}


}

