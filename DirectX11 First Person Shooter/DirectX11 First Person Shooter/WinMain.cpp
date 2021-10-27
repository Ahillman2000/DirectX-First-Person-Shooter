// include the windows and direct3d header files
#include <Windows.h>
#include "Window.h"
#include "Application.h"
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

// entry point for the windows program
int CALLBACK  WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	return Application{}.Run();
}
