#pragma once
#include "Windows.h"
#include <d3d11.h>
#include <wrl.h>
#include "Settings.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator = (const Renderer&) = delete;
	~Renderer() = default;
	void RenderFrame();
	void ClearBuffer(float red, float green, float blue);

	void Draw(float angle, float x_pos, float y_pos, float z_pos);

	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;

	Settings settings;

private:
	Microsoft::WRL::ComPtr <IDXGISwapChain>         swapChain;
	Microsoft::WRL::ComPtr <ID3D11Device>           d3ddev;
	Microsoft::WRL::ComPtr <ID3D11DeviceContext>    devcon;
	Microsoft::WRL::ComPtr <ID3D11RenderTargetView> backbuffer;
	Microsoft::WRL::ComPtr <ID3D11DepthStencilView> DSV;

	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;
};