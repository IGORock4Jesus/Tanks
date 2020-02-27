#include "Application.h"
#include <vector>
#include "IApplicationLayer.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"

class ApplicationImpl {
	std::vector<IApplicationLayer*> layers;
	HINSTANCE hinstance;

	Window* window;
	Renderer* renderer;
	Input* input;

public:
	ApplicationImpl()
		: hinstance{ GetModuleHandle(nullptr) }
	{
		window = new Window(hinstance, 800, 600);
		layers.push_back(window);

		renderer = new Renderer(window);
		layers.push_back(renderer);

		input = new Input(hinstance, window->GetHandle());
		layers.push_back(input);
	}

	~ApplicationImpl()
	{
		for (auto& layer : layers)
			delete layer;
	}

	void Run()
	{
		for (auto& layer : layers)
			layer->Update();
	}

	Window* GetWindow() { return window; }
	Renderer* GetRenderer() { return renderer; }
	Input* GetInput() { return input; }
};

Application::Application()
	: enable{ false }
{
	impl = new ApplicationImpl();
	GetWindow()->Closed.Add([this](Window* w) { this->Close(); });
}

Application::~Application()
{
	delete impl;
}

void Application::Run()
{
	DWORD oldTime = timeGetTime();

	while (enable)
	{
		impl->Run();

		DWORD newTime = timeGetTime();
		float elapsedTime = (newTime - oldTime) * 0.001f;
		oldTime = newTime;

		OnUpdate(elapsedTime);
	}
}

void Application::Close()
{
	enable = false;
}

Window* Application::GetWindow()
{
	return impl->GetWindow();
}

Renderer* Application::GetRenderer()
{
	return impl->GetRenderer();
}

Input* Application::GetInput()
{
	return impl->GetInput();
}