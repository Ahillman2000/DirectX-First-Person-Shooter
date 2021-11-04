#include "Application.h"
#include "Settings.h"
#include <fstream>

Application::Application()
	:
	wnd(settings.SCREEN_WIDTH, settings.SCREEN_HEIGHT, "DirectX11 First Person Shooter")
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

	wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);

	//wnd.Gfx().Draw(timer.Peek(), 0, 0.5, 5);
	//wnd.Gfx().Draw(0, 0, 0.5, 4.5 + c);

	std::fstream level;
	level.open("Level.txt");

	char wallChar = '#';
	char endline = 'e';

	int line    = 0;
	int coloumn = 0;

	while(!level.eof())
	{
		line++;

		if (/*level.get() == endline*/ line == 6)
		{
			coloumn++;
			line = 0;
		}

		if (level.get() == wallChar)
		{
			wnd.Gfx().Draw((line * 2) - 5, (coloumn * 2) - 3, 5);
		}
	}
	level.close();

	wnd.Gfx().RenderFrame();
}
