#include "Camera.h"

void Camera::Initialize()
{
	 
}

void Camera::Update()
{
	camRotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget = DirectX::XMVector3TransformCoord(defaultForward, camRotationMatrix);

	camTarget = DirectX::XMVector3Normalize(camTarget);

	DirectX::XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = DirectX::XMMatrixRotationY(camYaw);

    camRight = DirectX::XMVector3TransformCoord(defaultRight, RotateYTempMatrix);
    camUp = DirectX::XMVector3TransformCoord(camUp, RotateYTempMatrix);
    camForward = DirectX::XMVector3TransformCoord(defaultForward, RotateYTempMatrix);

    camPosition += moveLeftRight * camRight;
    camPosition += moveBackForward * camForward;

    moveLeftRight = 0.0f;
    moveBackForward = 0.0f;

    camTarget = camPosition + camTarget;

    camView = DirectX::XMMatrixLookAtLH(camPosition, camTarget, camUp);
}
