#include "Input.h"
#include <map>
#include <dinput.h>
#include <wrl.h>
#include "Window.h"


namespace Input
{
Microsoft::WRL::ComPtr<IDirectInput8> direct;
Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard;
char keyState[256];
std::map<std::wstring, bool> keys;

std::wstring GetName(size_t key) {
	switch (key)
	{
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

bool IskeyDown(std::wstring key) {
	if (keys.contains(key))
		return keys[key];
	return false;
}

bool Initialize(HINSTANCE hinstance)
{
	if (FAILED(DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, &direct, nullptr)))
		return false;

	if (FAILED(direct->CreateDevice(GUID_SysKeyboard, &keyboard, nullptr)))
		return false;

	if (FAILED(keyboard->SetCooperativeLevel(Window::GetHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return false;

	if (FAILED(keyboard->SetDataFormat(&c_dfDIKeyboard)))
		return false;

	if (FAILED(keyboard->Acquire()))
		return false;

	return true;
}

void Release()
{
	keyboard->Unacquire();
}

void KeyDown(size_t key) {
	keys[GetName(key)] = true;
}
void KeyUp(size_t key) {
	keys[GetName(key)] = false;
}
void Update()
{
	char newKeyState[256];
	keyboard->GetDeviceState(256, newKeyState);

	if (memcmp(newKeyState, keyState, 256)) {
		for (size_t i = 0; i < 256; i++)
		{
			if (newKeyState[i] != keyState[i]) {
				if (newKeyState[i] & 0x80)
					KeyDown(i);
				else
					KeyUp(i);
			}
		}
		memcpy(keyState, newKeyState, 256);
	}
}

};

