#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <vector>

class IndexBuffer
{
public:
	void Init(ID3D11Device* d3ddev, const std::vector<unsigned short> indices);
	void Bind(ID3D11DeviceContext* devcon);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC  ibd = {  };

	D3D11_SUBRESOURCE_DATA isd = {};
};

