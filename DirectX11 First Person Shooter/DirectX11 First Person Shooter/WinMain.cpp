#include<Windows.h>
#include <d3d9.h>

#pragma comment (lib, "d3d9.lib")

LPDIRECT3D9 d3d;
LPDIRECT3DDEVICE9 d3ddev;

void InitD3D(HWND hwnd);
void RenderFrame(void);
void CleanD3D(void);

void InitD3D(HWND hWnd)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;

	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
}

void RenderFrame(void)
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

	d3ddev->BeginScene();

	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void CleanD3D(void)
{
	d3ddev->Release();
	d3d->Release();
}


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
		0, pClassName, windowName, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, x_pos, y_pos, width, height, nullptr, nullptr, hInstance, nullptr
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