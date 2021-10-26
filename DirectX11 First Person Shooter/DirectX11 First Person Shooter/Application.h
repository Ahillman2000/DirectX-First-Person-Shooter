#pragma once
#include "Window.h"
#include "windows.h"
#include "Time.h"

class Application
{
public:
	Application();
	int Run();

private:
	void DoFrame();

	Window wnd;
	Time timer;
};

