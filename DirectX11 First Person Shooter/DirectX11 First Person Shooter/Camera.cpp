#include "Camera.h"
#include "magic.h"
#include <queue>

// Jpres
/*Camera::Camera()
{
	pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	posVector = DirectX::XMLoadFloat3(&pos);

	rot = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	rotVector = DirectX::XMLoadFloat3(&rot);
	UpdateViewMatrix();
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = (fovDegrees / 360.0f) * DirectX::XM_2PI;
	projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

const DirectX::XMMATRIX& Camera::GetViewMatrix() const
{
	return viewMatrix;
}

const DirectX::XMMATRIX& Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

const DirectX::XMVECTOR& Camera::GetPositionVector() const
{
	return posVector;
}

const DirectX::XMFLOAT3& Camera::GetPositionFloat3() const
{
	return pos;
}

const DirectX::XMFLOAT3& Camera::GetRotationFloat3() const
{
	return rot;
}

void Camera::SetPositon(const DirectX::XMVECTOR& _pos)
{
	DirectX::XMStoreFloat3(&pos, _pos);
	posVector = _pos;
	UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
	pos = DirectX::XMFLOAT3(x, y, z);
	posVector = DirectX::XMLoadFloat3(&pos);
	UpdateViewMatrix();
}

void Camera::AdjustPositon(const DirectX::XMVECTOR& _pos)
{
	posVector = DirectX::XMVectorAdd(posVector, _pos);
	DirectX::XMStoreFloat3(&pos, posVector);
	UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;

	posVector = XMLoadFloat3(&pos);
	UpdateViewMatrix();
}

void Camera::SetRotation(const DirectX::XMVECTOR& _rot)
{
	rotVector = _rot;
	DirectX::XMStoreFloat3(&rot, _rot);
	UpdateViewMatrix();
}

void Camera::SetRotation(float x, float y, float z)
{
	rot = DirectX::XMFLOAT3(x, y, z);
	rotVector = DirectX::XMLoadFloat3(&rot);
	UpdateViewMatrix();
}

void Camera::AdjustRotation(const DirectX::XMVECTOR& _rot)
{
	rotVector = DirectX::XMVectorAdd(rotVector, _rot);
	DirectX::XMStoreFloat3(&rot, rotVector);
	UpdateViewMatrix();
}

void Camera::AdjustRotation(float x, float y, float z)
{
	rot.x += x;
	rot.y += y;
	rot.z += z;

	rotVector = DirectX::XMLoadFloat3(&rot);
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	DirectX::XMMATRIX camRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(rot.x, rot.y, rot.z);
	DirectX::XMVECTOR camTarget = DirectX::XMVector3TransformCoord(DEFAULT_FORWARD_VECTOR, camRotationMatrix);

	camTarget = DirectX::XMVectorAdd(camTarget, posVector);

	DirectX::XMVECTOR upDir = DirectX::XMVector3TransformCoord(DEFAULT_UP_VECTOR, camRotationMatrix);

	viewMatrix = DirectX::XMMatrixLookAtLH(posVector, camTarget, upDir);
}*/

Camera::Camera() noexcept
{
	Reset();
}

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	const auto lookVector = DirectX::XMVector3Transform(DEFAULT_FORWARD_VECTOR, DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f));

	const auto camPosition = DirectX::XMLoadFloat3(&pos);
	const auto camTarget = DirectX::XMVectorAdd(camPosition, lookVector);

	return DirectX::XMMatrixLookAtLH(camPosition, camTarget, DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
}

void Camera::Reset() noexcept
{
	pos   = { 0.0f, 0.0f, 0.0f };
	pitch = 0.0f;
	yaw   = 0.0f;
}

void Camera::Rotate(float dx, float dy) noexcept
{
	yaw = wrap_angle(yaw + dx * camRotationSpeed);
	pitch = std::clamp(static_cast<const float>(pitch + dy * camRotationSpeed), static_cast<const float>(-3.14f / 2.0f), static_cast<const float>(3.14 / 2.0f));
}

void Camera::Translate(DirectX::XMFLOAT3 translation) noexcept
{
	DirectX::XMStoreFloat3(&translation, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&translation), DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f) * DirectX::XMMatrixScaling(camTranslationSpeed, camTranslationSpeed, camTranslationSpeed)));

	pos =
	{
		pos.x + translation.x,
		pos.y + translation.y,
		pos.z + translation.z
	};
}