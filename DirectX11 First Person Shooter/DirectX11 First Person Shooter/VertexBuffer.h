 #pragma once
#include <wrl.h>
#include <d3d11.h>
#include <wrl.h>
#include <memory>
#include <vector>
#include "Vertex.h"

class VertexBuffer
{
	
public:
	void Init(ID3D11Device* d3ddev, const std::vector<Vertex>& vertices);
	void Bind(ID3D11DeviceContext* devcon);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	
	D3D11_BUFFER_DESC bdsc = {};
	UINT bufferSize = 0;
	
	UINT stride;
};
