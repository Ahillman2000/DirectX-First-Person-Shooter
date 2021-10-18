// include the windows and direct3d header files
#include<Windows.h>
#include <d3d9.h>

// include the direct3d library file
#pragma comment (lib, "d3d9.lib")

// defines the resolution of the screen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// pointer to direct3d interface
LPDIRECT3D9 d3d;
// pointer to device class
LPDIRECT3DDEVICE9 d3ddev;

// pointer to vertex buffer
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;

void InitD3D(HWND hwnd);
void RenderFrame(void);
void CleanD3D(void);
void InitGraphics(void);

// create a custom vertex format
struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;
	DWORD colour;
};
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

void InitD3D(HWND hWnd)
{
	// direct3d interface
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	// struct for device info
	D3DPRESENT_PARAMETERS d3dpp;

	// clear struct
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	// windowed program
	d3dpp.Windowed = TRUE;
	// discard old frames
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// window to use direct3d
	d3dpp.hDeviceWindow = hWnd;

	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	InitGraphics();
}

void RenderFrame(void)
{
	//DWORD clearColour = D3DCOLOR_XRGB(137, 207, 240);
	DWORD clearColour = D3DCOLOR_XRGB(0, 0, 0);

	// clear window 
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, clearColour, 1.0f, 0);

	d3ddev->BeginScene();

	// set FVF code with custom struct
	d3ddev->SetFVF(CUSTOMFVF);
	// set vertex buffer to draw from
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	// draw vertices to screen
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	d3ddev->EndScene();

	// display frame
	d3ddev->Present(NULL, NULL, NULL, NULL);
}

void CleanD3D(void)
{
	// close and release to clean
	v_buffer->Release();
	d3ddev->Release();
	d3d->Release();
}

void InitGraphics(void)
{
	CUSTOMVERTEX vertices[] =
	{
		// vectices of a triangle from top clockwise
		{400.0f, 62.5f , 0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255)},
		{650.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0)},
		{150.0f, 500.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0)},
	};

	// create a vertex buffer
	d3ddev->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX), 0, CUSTOMFVF, D3DPOOL_MANAGED, &v_buffer, NULL);

	VOID* pVoid;
	// lock buffer
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	// copy vertices to vertex buffer
	memcpy(pVoid, vertices, sizeof(vertices));
	// release buffer
	v_buffer->Unlock();
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
		0, pClassName, windowName, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, x_pos, y_pos, SCREEN_WIDTH, SCREEN_HEIGHT, nullptr, nullptr, hInstance, nullptr
	);

	ShowWindow(hWnd, SW_SHOW);

	InitD3D(hWnd);

	MSG msg;

	BOOL gResult;

	while((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		RenderFrame();
	}
	CleanD3D();

	if (gResult == -1)
	{
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}