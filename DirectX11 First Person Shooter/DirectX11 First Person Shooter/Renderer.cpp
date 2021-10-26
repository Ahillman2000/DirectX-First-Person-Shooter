#include "Renderer.h"

#pragma comment(lib, "d3d11.lib")

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd = {};

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = 0;
	scd.BufferDesc.Height = 0;
	scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;

	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&d3ddev,
		nullptr,
		&devcon
	);

	ID3D11Resource* pBackBuffer = nullptr;

	swapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	
	d3ddev->CreateRenderTargetView(
		pBackBuffer,
		nullptr,
		&backbuffer
	);

	pBackBuffer->Release();
}

Renderer::~Renderer()
{
	if (backbuffer != nullptr)
	{
		backbuffer->Release();
	}
	if (d3ddev != nullptr)
	{
		devcon->Release();
	}
	if (swapChain != nullptr)
	{
		swapChain->Release();
	}
	if (d3ddev != nullptr)
	{
		d3ddev->Release();
	}
}

void Renderer::RenderFrame()
{
	swapChain->Present(1u, 0u);
}

void Renderer::ClearBuffer(float red, float green, float blue)
{
	const float colour[] = { red, green, blue, 1.0f };
	devcon->ClearRenderTargetView(backbuffer, colour);
}
