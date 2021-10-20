#include "Application.h"

Application::Application()
	:
	wnd(800, 600, "DirectX11 First Person Shooter")
{}

int Application::Go()
{
	MSG msg;

	BOOL gResult;

	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		DoFrame();
	}

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}

	//return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Application::DoFrame()
{
	wnd.Gfx().EndFrame();
}