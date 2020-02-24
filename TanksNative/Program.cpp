#include "Log.h"
#include "Window.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "UpdateManager.h"
#include "LevelConstructor.h"
#include "Input.h"


int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE, LPWSTR, int) {
	if (!Window::Initialize(hinstance, 800, 600)) {
		Log::WriteLine(L"Window::Initialize() - failed");
		return 0;
	}
	if (!Renderer::Initialize()) {
		Log::WriteLine(L"Renderer::Initialize() - failed");
		return 0;
	}
	if (!ResourceManager::LoadAll()) {
		Log::WriteLine(L"ResourceManager::LoadAll() - failed");
		return 0;
	}
	if(!Input::Initialize(hinstance)) {
		Log::WriteLine(L"Input::Initialize() - failed");
		return 0;
	}

	Renderer::SetTexture(ResourceManager::GetTexture());

	LevelConstructor::Construct(ResourceManager::GetLevel(L"28"));

	UpdateManager::Start();
	Window::Run();
	UpdateManager::Stop();

	Input::Release();
	Renderer::Release();
	ResourceManager::Release();
	return 0;
}

