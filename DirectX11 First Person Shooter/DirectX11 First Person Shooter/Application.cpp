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
		Update();
	}
}

void Application::Update()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;

	wnd.Gfx().ClearBuffer(255.0f, 255.0f, 255.0f);

	wnd.Gfx().Draw(timer.Peek(), 0, 0.5, 5);
	wnd.Gfx().Draw(0, 0, 0.5, 4.5 + c);
	wnd.Gfx().RenderFrame();
}
