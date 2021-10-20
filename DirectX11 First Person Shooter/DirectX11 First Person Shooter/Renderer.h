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
	void EndFrame();

private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
};