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

	void MoveCamera();

	void GenerateLevel();

	Window wnd;
	Time timer;

	Camera camera;
	Keyboard keyboard;

	float block_spacing = 2;
	float map_x_offset = -8;
	float map_z_offset = -10; 
};
