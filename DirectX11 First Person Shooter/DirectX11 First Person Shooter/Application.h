#pragma once
#include "Window.h"
#include "windows.h"
#include "Time.h"
#include "Settings.h"

class Application
{
public:
	Application();
	int Run();

	Settings settings;

private:
	void Update();

	Window wnd;
	Time timer;
};
