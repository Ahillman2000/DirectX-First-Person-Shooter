#include "Renderer.h"
#include <d3dcompiler.h>
#include <sstream>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC scd = {};

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferDesc.Width = 0;
	scd.BufferDesc.Height = 0;
	scd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;

	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1;
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0;

	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&scd,
		&swapChain,
		&d3ddev,
		nullptr,
		&devcon
	);

	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;

	swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	
	d3ddev->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr,
		&backbuffer
	);

	pBackBuffer->Release();
}

void Renderer::RenderFrame()
{
	swapChain->Present(1u, 0u);
}

void Renderer::ClearBuffer(float red, float green, float blue)
{
	const float colour[] = { red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f };
	devcon->ClearRenderTargetView(backbuffer.Get(), colour);
}

void Renderer::DrawTestTriangle(float angle)
{
	struct Vertex
	{
		struct 
		{
			float x;
			float y;
		} pos;

		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		} color;
	};

	Vertex vertices[]
	{
		{ 0.0f,  0.5f, 255, 0, 0, 0},
		{ 0.5f, -0.5f, 0, 255, 0, 0},
		{-0.5f, -0.5f, 0, 0, 255, 0},
		{-0.3f,  0.3f, 0, 255, 0, 0},
		{ 0.3f,  0.3f, 0, 0, 255, 0},
		{ 0.0f, -0.8f, 255, 0, 0, 0},
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bdsc = {};
	bdsc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bdsc.Usage = D3D11_USAGE_DEFAULT;
	bdsc.CPUAccessFlags = 0u;
	bdsc.MiscFlags = 0u;
	bdsc.ByteWidth = sizeof(vertices);
	bdsc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA srd = {};
	srd.pSysMem = vertices;

	d3ddev->CreateBuffer(&bdsc, &srd, &pVertexBuffer);
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;

	const unsigned short indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 1,
		2, 1, 5,
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC  ibd = {  };
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	d3ddev->CreateBuffer(&ibd, &isd, &pIndexBuffer);
	devcon->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	devcon->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	struct ConstantBuffer
	{
		struct
		{
			float element[4][4];
		}transformation;
	};

	const ConstantBuffer cb =
	{
		{
			0.75f * std::cos(angle), std::sin(angle), 0.0f, 0.0f,
			0.75f * -std::sin(angle), std::cos(angle), 0.0f, 0.0f,
			0.0f,            0.0f,            1.0f, 0.0f,
			0.0f,            0.0f,            0.0f, 1.0f,
		}
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	d3ddev->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	
	devcon->VSSetConstantBuffers(0, 1, pConstantBuffer.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	d3ddev->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	devcon->PSSetShader(pPixelShader.Get(), nullptr, 0);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	d3ddev->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	devcon->VSSetShader(pVertexShader.Get(), nullptr, 0);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	d3ddev->CreateInputLayout(
		ied,
		(UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout);

	devcon->IASetInputLayout(pInputLayout.Get());
	devcon->OMSetRenderTargets(1, backbuffer.GetAddressOf(), nullptr);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	devcon->RSSetViewports(1, &vp);

	//devcon->DrawIndexed((UINT)std::size(vertices), 0u);
	devcon->DrawIndexed((UINT)std::size(indices), 0, 0);
}
