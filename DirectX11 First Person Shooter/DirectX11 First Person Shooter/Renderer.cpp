#include "Renderer.h"
#include <d3dcompiler.h>
#include <sstream>
#include <DirectXMath.h>
#include "Settings.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Renderer::Renderer(HWND hWnd)
{
	// SWAPCHAIN
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

	// DEPTH STENCIL
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
	d3ddev->CreateDepthStencilState(&dsDesc, &pDSState);
	devcon->OMSetDepthStencilState(pDSState.Get(), 1);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width  = settings.SCREEN_WIDTH;
	descDepth.Height = settings.SCREEN_HEIGHT;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count   = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage     = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	d3ddev->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format        = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	d3ddev->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &DSV);
	devcon->OMSetRenderTargets(1, backbuffer.GetAddressOf(), DSV.Get());

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
	devcon->ClearDepthStencilView(DSV.Get(), D3D11_CLEAR_DEPTH, 1, 0);
}

void Renderer::Draw(float angle, float x_pos, float y_pos, float z_pos)
{
	std::vector<Vertex> vertices =
	{
		{-1.0f, -1.0f, -1.0f},
		{ 1.0f, -1.0f, -1.0f },
		{ -1.0f,  1.0f, -1.0f },
		{ 1.0f,  1.0f, -1.0f },
		{ -1.0f, -1.0f,  1.0f },
		{ 1.0f, -1.0f,  1.0f },
		{ -1.0f,  1.0f,  1.0f },
		{ 1.0f,  1.0f,  1.0f },
	};

	const std::vector<unsigned short> indices =
	{
		0, 2, 1,  2, 3, 1,
		1, 3, 5,  3, 7, 5,
		2, 6, 3,  3, 6, 7,
		4, 5, 7,  4, 7, 6,
		0, 4, 2,  2, 4, 6,
		0, 1, 4,  1, 5, 4
	};

	// CREATE AND BIND VERTEX BUFFER
	vertexBuffer.Init(d3ddev.Get(), vertices);
	vertexBuffer.Bind(devcon.Get());

	// CREATE AND BIND INDEX BUFFER
	indexBuffer.Init(d3ddev.Get(), indices);
	indexBuffer.Bind(devcon.Get());

	// CONSTANT BUFFER
	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
	};

	DirectX::XMMATRIX worldView = DirectX::XMMatrixIdentity();

	const ConstantBuffer cb =
	{
		{
			DirectX::XMMatrixTranspose(
				DirectX::XMMatrixRotationZ(angle) *
				DirectX::XMMatrixRotationX(angle) *
				DirectX::XMMatrixTranslation(x_pos, y_pos, z_pos + 4.0f) *
				GetCamera()*
				GetProjection() *
				DirectX::XMMatrixPerspectiveLH(1.0f, 0.75f, 0.5f, 10.0f))
		}
	};

	// VERTEX CONSTANT BUFFER
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	d3ddev->CreateBuffer(&cbd, &csd, &vertexConstantBuffer);
	
	devcon->VSSetConstantBuffers(0, 1, vertexConstantBuffer.GetAddressOf());

	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colours[6];
	};

	const ConstantBuffer2 cb2 = 
	{
		{
			{1.0f, 0.0f, 1.0f},
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{1.0f, 1.0f, 0.0f},
			{0.0f, 1.0f, 1.0f},
		}
	};

	// INDEX CONSTANT BUFFER
	Microsoft::WRL::ComPtr<ID3D11Buffer> indexConstantBuffer;
	D3D11_BUFFER_DESC cbd2;
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.CPUAccessFlags = 0;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;
	d3ddev->CreateBuffer(&cbd2, &csd2, &indexConstantBuffer);
	devcon->PSSetConstantBuffers(0, 1, indexConstantBuffer.GetAddressOf()); 

	// SHADERS
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
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	d3ddev->CreateInputLayout(
		ied,
		(UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout);

	devcon->IASetInputLayout(pInputLayout.Get());
	//devcon->OMSetRenderTargets(1, backbuffer.GetAddressOf(), nullptr);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT vp;
	vp.Width    = settings.SCREEN_WIDTH;
	vp.Height   = settings.SCREEN_HEIGHT;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	devcon->RSSetViewports(1, &vp);

	//devcon->DrawIndexed((UINT)std::size(vertices), 0u);
	devcon->DrawIndexed((UINT)std::size(indices), 0, 0);
}

// CAMERA RELATED STUFF
void Renderer::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
	projection = proj;
}

DirectX::XMMATRIX Renderer::GetProjection() const noexcept
{
	return projection;
}

void Renderer::SetCamera(DirectX::FXMMATRIX cam) noexcept
{
	camera = cam;
}

DirectX::XMMATRIX Renderer::GetCamera() const noexcept
{
	return camera;
}
