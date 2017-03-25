
#pragma once

#include "Render/Device.h"
#include "d3d11.h"

class DeviceDX11 : public Device
{
	friend class Render;
	friend class GeometryBufferDX11;
	friend class ShaderDX11;
	friend class TextureDX11;

	class ID3D11Device*	          pd3dDevice;
	class ID3D11DeviceContext*    immediateContext;
	class IDXGISwapChain*         swapChain;
	class ID3D11RenderTargetView* renderTargetView;
	class ID3D11Texture2D*        depthStencil;
	class ID3D11DepthStencilView* depthStencilView;
	class IDXGIFactory1* factory;

	struct D3D11_DEPTH_STENCIL_DESC* ds_desc;
	class ID3D11DepthStencilState*   ds_state;

	HWND hwnd;

	DeviceDX11();
	virtual bool Init(int width, int height, void* data);
	virtual void Release();
	
	void RecreateSwapchain(int wgt, int hgt);

	virtual Shader* CreateShader(Shader::Type type, const char* name);

public:

	static DeviceDX11* instance;

	virtual void Clear(bool renderTarget, Color color, bool zbuffer, float zValue);
	virtual void Present();
	virtual GeometryBuffer* CreateBuffer(int size, int stride);
	virtual void SetVertexBuffer(int slot, GeometryBuffer* buffer);

	virtual Texture* CreateTexture(int w, int h, Texture::Format f, int l, Texture::Type tp);

	int GetPrimitiveType(Primitive type);
	int CalcPrimCount(Primitive type, int primCount);
	virtual void Draw(Primitive prim, int startVertex, int primCount);
};