#include "Application.h"
#include <vector>
#include "IApplicationLayer.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"

class ApplicationImpl {
	std::vector<IApplicationLayer*> layers;
	bool enable;
	HINSTANCE hinstance;

	Window* window;
	Renderer* renderer;
	Input* input;

public:
	ApplicationImpl()
		: enable{ false }, hinstance{ GetModuleHandle(nullptr) }
	{
		window = new Window(hinstance, 800, 600);
		window->Closed.Add([this](Window* w) { this->Close(); });
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
		enable = true;
		while (enable)
		{
			for (auto& layer : layers)
				layer->Update();
		}
	}

	void Close()
	{
		enable = false;
	}

	Window* GetWindow() { return window; }
	Renderer* GetRenderer() { return renderer; }
	Input* GetInput() { return input; }
};

Application::Application()
{
	impl = new ApplicationImpl();
}

Application::~Application()
{
	delete impl;
}

void Application::Run()
{
	impl->Run();
}

void Application::Close()
{
	impl->Close();
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