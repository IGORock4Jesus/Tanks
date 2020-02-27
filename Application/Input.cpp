#include "Input.h"
#include <exception>

std::wstring GetName(size_t key) {
	switch (key)
	{
		// spec-symbols
	case DIK_ESCAPE:
		return L"Escape";

		// literals
	case DIK_W:
		return L"W";
	case DIK_S:
		return L"S";
	case DIK_A:
		return L"A";
	case DIK_D:
		return L"D";
	case DIK_J:
		return L"J";
	case DIK_K:
		return L"K";
	default:
		return L"Unknown";
	}
}

Input::Input(HINSTANCE hinstance, HWND hwnd)
{
	ZeroMemory(keyState, 256);

	if (FAILED(DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&direct, nullptr)))
		throw std::exception();

	if (FAILED(direct->CreateDevice(GUID_SysKeyboard, &keyboard, nullptr)))
		throw std::exception();

	if (FAILED(keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		throw std::exception();

	if (FAILED(keyboard->SetDataFormat(&c_dfDIKeyboard)))
		throw std::exception();

	if (FAILED(keyboard->Acquire()))
		throw std::exception();
}

Input::~Input()
{
	keyboard->Unacquire();
	keyboard->Release();
	direct->Release();
}

void Input::Update()
{
	try
	{
		char newKeyState[256]{ 0 };
		HRESULT hr = keyboard->GetDeviceState(256, newKeyState);
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED) {
			keyboard->Acquire();
			hr = keyboard->GetDeviceState(256, newKeyState);
			if (hr == DIERR_INPUTLOST)
				return;
		}

		if (memcmp(newKeyState, keyState, 256)) {
			for (size_t i = 0; i < 256; i++)
			{
				if (newKeyState[i] != keyState[i]) {
					if (newKeyState[i] & 0x80)
						KeyDown(GetName(i));
					else
						KeyUp(GetName(i));
				}
			}
			memcpy(keyState, newKeyState, 256);
		}
	}
	catch (const std::exception & ex)
	{
		OutputDebugStringA(ex.what());
		OutputDebugStringA("\r\n");
	}
	catch (...) {
		OutputDebugStringA("Input::Update() - raised an unknown exception.\r\n");
	}
}