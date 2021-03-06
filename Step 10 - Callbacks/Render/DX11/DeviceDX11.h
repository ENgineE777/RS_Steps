
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

	struct D3D11_BLEND_DESC* blend_desc;
	class ID3D11BlendState*  blend_state;
	bool                     blend_changed;

	struct D3D11_DEPTH_STENCIL_DESC* ds_desc;
	class ID3D11DepthStencilState*   ds_state;
	int                              ds_stencil_ref;
	bool                             ds_changed;

	struct D3D11_RASTERIZER_DESC* raster_desc;
	class ID3D11RasterizerState*  raster_state;
	bool                          raster_changed;

	int  scr_w;
	int  scr_h;
	bool vp_was_setted;

	HWND hwnd;

	DeviceDX11();
	virtual bool Init(int width, int height, void* data);
	virtual void Release();
	
	void RecreateSwapchain(int wgt, int hgt);

	virtual Shader* CreateShader(Shader::Type type, const char* name);
	void UpdateStates();

public:

	static DeviceDX11* instance;

	virtual void Clear(bool renderTarget, Color color, bool zbuffer, float zValue);
	virtual void Present();
	virtual GeometryBuffer* CreateBuffer(int size, int stride);
	virtual void SetVertexBuffer(int slot, GeometryBuffer* buffer);

	virtual Texture* CreateTexture(int w, int h, Texture::Format f, int l, bool rt, Texture::Type tp);

	int GetPrimitiveType(Primitive type);
	int CalcPrimCount(Primitive type, int primCount);
	virtual void Draw(Primitive prim, int startVertex, int primCount);

	virtual void SetAlphaBlend(bool enable);
	virtual void SetBlendFunc(BlendArg src, BlendArg dest);
	virtual void SetBlendOperation(BlendOp op);
	virtual void SetDepthTest(bool enable);
	virtual void SetDepthWriting(bool enable);
	virtual void SetDepthFunc(CompareFunc func);
	virtual void SetCulling(CullMode mode);
	virtual void SetupSlopeZBias(bool enable, float slopeZBias, float depthOffset);
};