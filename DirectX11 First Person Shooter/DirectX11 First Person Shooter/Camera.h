#pragma once
#include <DirectXMath.h>

// Jpres
/*#include "Windows.h"

#include <d3dcompiler.h>
#include <directxmath.h>
#include <wrl.h>

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

class Camera
{
public:

	Camera();
	//~Camera() = delete;

	void SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ);;
	
	const DirectX::XMMATRIX& GetViewMatrix() const;
	const DirectX::XMMATRIX& GetProjectionMatrix() const;

	const DirectX::XMVECTOR& GetPositionVector() const;
	const DirectX::XMFLOAT3& GetPositionFloat3() const;

	const DirectX::XMMATRIX& GetRotationVector() const;
	const DirectX::XMFLOAT3& GetRotationFloat3() const;

	void SetPositon(const DirectX::XMVECTOR & pos);
	void SetPosition(float x, float y, float z);

	void AdjustPositon(const DirectX::XMVECTOR& pos);
	void AdjustPosition(float x, float y, float z);

	void SetRotation(const DirectX::XMVECTOR & rot);
	void SetRotation(float x, float y, float z);

	void AdjustRotation(const DirectX::XMVECTOR& rot);
	void AdjustRotation(float x, float y, float z);

	void Reset();

private:

	void UpdateViewMatrix();

	DirectX::XMVECTOR posVector;
	DirectX::XMVECTOR rotVector;
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 rot;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;

	const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
};*/

class Camera
{
public:
	Camera() noexcept;
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void Reset() noexcept;
	void Rotate(float dx, float dy) noexcept;
	void Translate(DirectX::XMFLOAT3 translation) noexcept;

private:
	DirectX::XMFLOAT3 pos;
	float pitch;
	float yaw;
	static constexpr float camTranslationSpeed = 10.0f;
	static constexpr float camRotationSpeed    =  1.0f;

	const DirectX::XMVECTOR DEFAULT_FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR DEFAULT_UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
};