#pragma once
#include "Window.h"

class Application
{
public:
	Application();
	int Go();

private:
	void DoFrame();

	Window wnd;
};

