#include "Application.h"
#include "Settings.h"
#include <fstream>

Application::Application()
	:
	wnd(settings.SCREEN_WIDTH, settings.SCREEN_HEIGHT, "DirectX11 First Person Shooter")
{
	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f));
}

int Application::Run()
{
	while (true)
	{
		if (const auto ecode = Window::ProcessMessage())
		{
			return *ecode;
			
		}

		wnd.Update();
		Update();
	}
}

void Application::Update()
{
	wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f);

	wnd.Gfx().SetCamera(camera.GetMatrix());

	MoveCamera();

	/*while (!wnd.keyboard.charBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
		std::string outmsg = "char: ";
		outmsg += ch;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
	}

	while (!wnd.keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent keyboardevent = keyboard.ReadKey();

		unsigned char keycode = keyboardevent.GetKeyCode();
		std::string outmsg = "keycode: ";
		outmsg += keycode;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
	}*/

	GenerateLevel();

	const float c = sin(timer.Peek()) / 2.0f + 0.5f;

	//wnd.Gfx().Draw(timer.Peek(), 0, 0.5, 5);
	//wnd.Gfx().Draw(0, 0, 0.5, 4.5 + c);

	wnd.Gfx().RenderFrame();
}

void Application::MoveCamera()
{
	if (wnd.keyboard.KeyIsPressed('W'))
	{
		camera.Translate({ 0.0f,0.0f,timer.Mark() });
	}
	if (wnd.keyboard.KeyIsPressed('S'))
	{
		camera.Translate({ 0.0f,0.0f,-timer.Mark() });
	}
	if (wnd.keyboard.KeyIsPressed('A'))
	{
		camera.Rotate(-timer.Mark(), 0.0f);
	}
	if (wnd.keyboard.KeyIsPressed('D'))
	{
		camera.Rotate(timer.Mark(), 0.0f);
	}

	/*if (wnd.keyboard.KeyIsPressed('R'))
	{
		camera.Translate({ 0.0f,timer.Mark(),0.0f });
	}
	if (wnd.keyboard.KeyIsPressed('F'))
	{
		camera.Translate({ 0.0f,-timer.Mark(),0.0f });
	}*/
}

void Application::GenerateLevel()
{
	std::fstream level;
	level.open("Level.txt");

	char wallChar = '#';
	char endline = '\n';

	int line = 0;
	int coloumn = 0;

	while (!level.eof())
	{
		line++;

		if (level.peek() == endline)
		{
			coloumn++;
			line = 0;
		}

		if (level.get() == wallChar)
		{
			// 0 rotation, x, y ,z = 5
			//wnd.Gfx().Draw(0.0f, (line * block_spacing) + map_x_offset, (coloumn * block_spacing) + map_y_offset, 5);
			wnd.Gfx().Draw(0.0f, (line * block_spacing) + map_x_offset, 0, (coloumn * block_spacing) + map_z_offset);
		}
	}
	level.close();
}
