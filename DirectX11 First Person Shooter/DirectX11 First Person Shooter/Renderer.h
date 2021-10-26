#pragma once
#include "Windows.h"
#include <d3d11.h>

class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator = (const Renderer&) = delete;
	~Renderer();
	void RenderFrame();
	void ClearBuffer(float red, float green, float blue);

private:
	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* d3ddev = nullptr;
	ID3D11DeviceContext* devcon = nullptr;
	ID3D11RenderTargetView* backbuffer = nullptr;
};