
#pragma once

#include "Render/Device.h"
#include "d3d11.h"

class DeviceDX11 : public Device
{
	friend class Render;

	HWND hwnd;

	class ID3D11Device*	          pd3dDevice;
	class ID3D11DeviceContext*    immediateContext;
	class IDXGISwapChain*         swapChain;
	class ID3D11RenderTargetView* renderTargetView;
	class ID3D11Texture2D*        depthStencil;
	class ID3D11DepthStencilView* depthStencilView;
	class IDXGIFactory1* factory;

	DeviceDX11();
	virtual bool Init(int width, int height, void* data);
	virtual void Release();
	
	void RecreateSwapchain(int wgt, int hgt);

public:
	virtual void Clear(bool renderTarget, Color color, bool zbuffer, float zValue);
	virtual void Present();
};