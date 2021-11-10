#pragma once
#include "Window.h"
#include "windows.h"
#include "Time.h"
#include "Settings.h"
#include "Camera.h"

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

	Camera camera;
	Keyboard keyboard;

	float block_spacing = 2;
	float map_x_offset = -7;
	float map_y_offset = -6; 
};
