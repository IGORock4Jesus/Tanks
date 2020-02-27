#pragma once

#include "APPLICATION_API.h"

class ApplicationImpl;
class Window;
class Renderer;
class Input;

class APPLICATION_API Application
{
	ApplicationImpl* impl;

public:
	Application();
	~Application();

	void Run();
	void Close();

	Window* GetWindow();
	Renderer* GetRenderer();
	Input* GetInput();
};
