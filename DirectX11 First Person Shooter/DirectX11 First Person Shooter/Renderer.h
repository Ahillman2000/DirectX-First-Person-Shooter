#pragma once
#include "Windows.h"
#include <d3d11.h>
#include <wrl.h>

class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator = (const Renderer&) = delete;
	~Renderer() = default;
	void RenderFrame();
	void ClearBuffer(float red, float green, float blue);

	void DrawTestTriangle(float angle);

private:
	Microsoft::WRL::ComPtr <IDXGISwapChain>         swapChain;
	Microsoft::WRL::ComPtr <ID3D11Device>           d3ddev;
	Microsoft::WRL::ComPtr <ID3D11DeviceContext>    devcon;
	Microsoft::WRL::ComPtr <ID3D11RenderTargetView> backbuffer;
};