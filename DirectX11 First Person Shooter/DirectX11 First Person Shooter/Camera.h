#pragma once
#include "Windows.h"

#include <d3dcompiler.h>
#include <directxmath.h>
#include <wrl.h>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

class Camera
{
public:
	Camera() = default;
	~Camera() = delete;

	void Initialize();
	void Update();

private:

	Microsoft::WRL::ComPtr <ID3D11Buffer> cbPerObjectBuffer;

	DirectX::XMVECTOR camPosition;
	DirectX::XMVECTOR camTarget;
	DirectX::XMVECTOR camUp;

	DirectX::XMVECTOR defaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR defaultRight   = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	DirectX::XMVECTOR camForward     = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DirectX::XMVECTOR camRight       = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	DirectX::XMMATRIX camRotationMatrix;
	DirectX::XMMATRIX groundWorld;

	float moveLeftRight   = 0.0f;
	float moveBackForward = 0.0f;

	float camYaw   = 0.0f;
	float camPitch = 0.0f;
};

