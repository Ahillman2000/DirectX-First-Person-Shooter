// include the windows and direct3d header files
#include<Windows.h>

// defines the resolution of the screen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(1);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void ClearBackground()
{
	
}

// entry point for the windows program
int CALLBACK  WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	const auto pClassName = L"DirectX";
	const auto windowName = L"First Person Shooter";

	HWND hWnd;
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;

	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);

	int x_pos = 200;
	int y_pos = 200;

	int width = 640;
	int height = 480;

	hWnd = CreateWindowEx(
		0, pClassName, windowName, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, x_pos, y_pos, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr
	);

	ShowWindow(hWnd, SW_SHOW);

	MSG msg;

	BOOL gResult;

	while((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}