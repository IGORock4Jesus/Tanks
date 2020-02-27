#include "Window.h"
#include <exception>
#include "Application.h"

LRESULT CALLBACK Window::StaticProcedure(HWND h, UINT m, WPARAM w, LPARAM l) {
	if (m == WM_NCCREATE) {
		LPCREATESTRUCT create = (LPCREATESTRUCT)l;
		Window* _this = (Window*)create->lpCreateParams;
		::SetWindowLongPtr(h, GWLP_USERDATA, (LONG_PTR)_this);
		return 1;
	}
	if (m == WM_NCDESTROY) {
		::SetWindowLongPtr(h, GWLP_USERDATA, 0);
		return 0;
	}

	Window* _this = (Window*)::GetWindowLongPtr(h, GWLP_USERDATA);
	return _this->Procedure(h, m, w, l);
}

LRESULT Window::Procedure(HWND h, UINT m, WPARAM w, LPARAM l) {
	switch (m)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(h, m, w, l);
	}
}

Window::Window(HINSTANCE hinstance, int width, int height)
{
	WNDCLASS wc{ 0 };
	wc.lpfnWndProc = StaticProcedure;
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hinstance;
	wc.lpszClassName = ClassName;
	RegisterClass(&wc);
	int sw = ::GetSystemMetrics(SM_CXSCREEN);
	int sh = ::GetSystemMetrics(SM_CYSCREEN);
	RECT rect{ sw / 2 - width / 2, sh / 2 - height / 2, sw / 2 + width / 2, sh / 2 + height / 2 };
	::AdjustWindowRect(&rect, WS_POPUPWINDOW, FALSE);
	handle = ::CreateWindow(ClassName, ClassName, WS_POPUPWINDOW, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, HWND_DESKTOP, nullptr, hinstance, this);
	if (!handle)
		throw std::exception("Ошибка при создании окна.");

	ShowWindow(handle, SW_NORMAL);
	UpdateWindow(handle);
}

void Window::Update()
{
	MSG msg;
	if (::PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

		if (msg.message == WM_QUIT)
			Closed(this);
	}
}