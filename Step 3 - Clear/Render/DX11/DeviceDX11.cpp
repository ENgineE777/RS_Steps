
#pragma once

#include "DeviceDX11.h"

DeviceDX11::DeviceDX11()
{
	pd3dDevice = NULL;
	immediateContext = NULL;
	swapChain = NULL;
	renderTargetView = NULL;
	depthStencil = NULL;
	depthStencilView = NULL;
	factory = NULL;
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

	//if( FAILED( hr ) )
	//return hr;	

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

void DeviceDX11::Release()
{
	delete this;
}