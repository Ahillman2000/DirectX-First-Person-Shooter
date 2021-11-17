#include "IndexBuffer.h"

void IndexBuffer::Init(ID3D11Device* d3ddev, const std::vector<unsigned short> indices)
{
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = indices.size() * sizeof(unsigned short);
	ibd.StructureByteStride = sizeof(unsigned short);

	isd.pSysMem = indices.data();

	d3ddev->CreateBuffer(&ibd, &isd, &pIndexBuffer);
}

void IndexBuffer::Bind(ID3D11DeviceContext *devcon)
{
	devcon->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

