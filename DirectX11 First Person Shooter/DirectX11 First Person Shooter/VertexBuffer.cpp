#include "VertexBuffer.h"

void VertexBuffer::Init(ID3D11Device* d3ddev, const std::vector<Vertex>& vertices)
{
	//bufferSize = numVertices;
	stride = sizeof(Vertex);

	D3D11_BUFFER_DESC bdsc = {};
	bdsc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bdsc.Usage = D3D11_USAGE_DEFAULT;
	bdsc.CPUAccessFlags = 0u;
	bdsc.MiscFlags = 0u;

	bdsc.ByteWidth = UINT(sizeof(Vertex) * vertices.size());
	bdsc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = vertices.data();

	d3ddev->CreateBuffer(&bdsc, &srd, &pVertexBuffer);
}

void VertexBuffer::Bind(ID3D11DeviceContext* devcon)
{
	const UINT offset = 0u;
	devcon->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
}
