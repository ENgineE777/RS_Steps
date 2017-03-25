
#pragma once

#include "DeviceDX11.h"
#include "GeometryBufferDX11.h"
#include "ShaderDX11.h"
#include "TextureDX11.h"

DeviceDX11* DeviceDX11::instance = NULL;

DeviceDX11::DeviceDX11()
{
	pd3dDevice = NULL;
	immediateContext = NULL;
	swapChain = NULL;
	renderTargetView = NULL;
	depthStencil = NULL;
	depthStencilView = NULL;
	factory = NULL;

	instance = this;

	ds_desc = new D3D11_DEPTH_STENCIL_DESC();
	ZeroMemory(ds_desc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	ds_state = NULL;

	ds_desc->DepthEnable = true;
	ds_desc->DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	ds_desc->DepthFunc = D3D11_COMPARISON_LESS;

	ds_desc->StencilEnable = false;
	ds_desc->StencilReadMask = 0xFF;
	ds_desc->StencilWriteMask = 0xFF;

	ds_desc->FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	ds_desc->FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	ds_desc->FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	ds_desc->FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	ds_desc->BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	ds_desc->BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	ds_desc->BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	ds_desc->BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
}

bool DeviceDX11::Init(int width, int height, void* data)
{
	hwnd = *((HWND*)data);

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_DRIVER_TYPE   driverType;
	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr;

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		driverType = driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &pd3dDevice, &featureLevel, &immediateContext);

		if (SUCCEEDED(hr))
		{
			break;
		}
	}

	CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&factory));

	RecreateSwapchain(width, height);

	return true;
}

void DeviceDX11::RecreateSwapchain(int wgt, int hgt)
{	
	RELEASE(depthStencilView)
	RELEASE(depthStencil)
	RELEASE(renderTargetView)
	RELEASE(swapChain)

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = wgt;
	sd.BufferDesc.Height = hgt;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	factory->CreateSwapChain(pd3dDevice, &sd, &swapChain);

	//if( FAILED( hr ) )
	//return hr;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = NULL;
	HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	//if( FAILED( hr ) )
	//return hr;

	hr = pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &renderTargetView);
	pBackBuffer->Release();

	if (FAILED(hr))
	{
		return;
	}

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = wgt;
	descDepth.Height = hgt;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = pd3dDevice->CreateTexture2D(&descDepth, NULL, &depthStencil);

	if (FAILED(hr))
	{
		return;
	}

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = pd3dDevice->CreateDepthStencilView(depthStencil, &descDSV, &depthStencilView);

	immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)wgt;
	vp.Height = (FLOAT)hgt;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	immediateContext->RSSetViewports(1, &vp);

	RELEASE(ds_state)
	instance->pd3dDevice->CreateDepthStencilState(ds_desc, &ds_state);
	immediateContext->OMSetDepthStencilState(ds_state, 255);
}

void DeviceDX11::Clear(bool renderTarget, Color color, bool zbuffer, float zValue)
{
	if (renderTarget)
	{
		immediateContext->ClearRenderTargetView(renderTargetView, (float*)&color.r);
	}

	if (zbuffer)
	{
		immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, zValue, 0);
	}
}

void DeviceDX11::Present()
{
	swapChain->Present(0, 0);
}

GeometryBuffer* DeviceDX11::CreateBuffer(int size, int stride)
{
	return new GeometryBufferDX11(size, stride);
}

void DeviceDX11::SetVertexBuffer(int slot, GeometryBuffer* buffer)
{
	ID3D11Buffer* vb = NULL;
	unsigned int stride = 0;

	if (buffer)
	{
		vb = (ID3D11Buffer*)buffer->GetData();
		stride = buffer->GetStride();
	}

	unsigned int offset = 0;
	immediateContext->IASetVertexBuffers(0, 1, &vb, &stride, &offset);
}

Shader* DeviceDX11::CreateShader(Shader::Type type, const char* name)
{
	return new ShaderDX11(type, name);
}

Texture* DeviceDX11::CreateTexture(int w, int h, Texture::Format f, int l, Texture::Type tp)
{
	return new TextureDX11(w, h, f, l, tp);
}

int DeviceDX11::GetPrimitiveType(Primitive type)
{
	int tp = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	switch (type)
	{
		case LineStrip:
		{
			tp = D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP;
		}
		break;
		case LinesList:
		{
			tp = D3D10_PRIMITIVE_TOPOLOGY_LINELIST;
		}
		break;
		case TriangleStrip:
		{
			tp = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		}
		break;
		case TrianglesList:
		{
			tp = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		}
		break;
	}

	return tp;
}

int DeviceDX11::CalcPrimCount(Primitive type, int primCount)
{
	int tp = primCount;

	switch (type)
	{
		case LineStrip:
		{
			tp = primCount + 1;
		}
		break;
		case LinesList:
		{
			tp = primCount * 2;
		}
		break;
		case TriangleStrip:
		{
			tp = primCount + 2;
		}
		break;
		case TrianglesList:
		{
			tp = primCount * 3;
		}
		break;
	}

	return tp;
}

void DeviceDX11::Draw(Primitive prim, int startVertex, int primCount)
{
	Device::Draw(prim, startVertex, primCount);

	immediateContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)GetPrimitiveType(prim));
	immediateContext->Draw(CalcPrimCount(prim, primCount), startVertex);
}

void DeviceDX11::Release()
{
	delete this;
}