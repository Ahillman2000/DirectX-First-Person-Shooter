#include "Application.h"

int SCREEN_WIDTH  = 800;
int SCREEN_HEIGHT = 600;

Application::Application()
	:
	wnd(SCREEN_WIDTH, SCREEN_HEIGHT, "DirectX11 First Person Shooter")
{}

int Application::Run()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessage())
		{
			return *ecode;
		}
		DoFrame();
	}
}

void Application::DoFrame()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	//wnd.Gfx().ClearBuffer(c, c, 1.0f);

	wnd.Gfx().ClearBuffer(51.0f, 87.0f, 255.0f);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().RenderFrame();
}
