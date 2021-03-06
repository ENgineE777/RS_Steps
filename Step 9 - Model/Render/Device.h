
#pragma once

#include "Helpers/Helpers.h"
#include "Shader.h"
#include "GeometryBuffer.h"
#include "Program.h"
#include "Texture.h"

class Device
{
	friend class Render;
	friend class Program;

	virtual bool Init(int width, int height, void* data) = 0;
	virtual void Release() = 0;

public:

	enum Primitive
	{
		LineStrip = 0,
		LinesList,
		TriangleStrip,
		TrianglesList
	};

	enum CullMode
	{
		CullNone = 0,
		CullCW,
		CullCCW
	};

	enum BlendOp
	{
		BlendAdd = 0,
		BlendSub,
		BlendRevSub,
		BlendMin,
		BlendMax
	};

	enum CompareFunc
	{
		CmpNever = 0,
		CmpLess,
		CmpEqual,
		CmpLessEqual,
		CmpGreater,
		CmpNotequal,
		CmpGreaterqual,
		CmpAlways,
	};

	enum BlendArg
	{
		ArgZero = 0,
		ArgOne,
		ArgSrcColor,
		ArgInvSrcColor,
		ArgSrcAlpha,
		ArgInvSrcAlpha,
		ArgDestAlpha,
		ArgInvDestAlpha,
		ArgDestColor,
		ArgInvDestColor
	};

	virtual void Clear(bool renderTarget, Color color, bool zbuffer, float zValue) = 0;
	virtual void Present() = 0;

	virtual GeometryBuffer* CreateBuffer(int size, int stride) = 0;
	virtual void SetVertexBuffer(int slot, GeometryBuffer* buffer) = 0;
	
	virtual Texture* CreateTexture(int w, int h, Texture::Format f, int l, Texture::Type tp) = 0;

	virtual void Draw(Primitive prim, int startVertex, int primCount)
	{
		if (Program::current)
		{
			Program::current->SetShaders();
		}
	}

	virtual void SetAlphaBlend(bool enable) = 0;
	virtual void SetBlendFunc(BlendArg src, BlendArg dest) = 0;
	virtual void SetBlendOperation(BlendOp op) = 0;
	virtual void SetDepthTest(bool enable) = 0;
	virtual void SetDepthWriting(bool enable) = 0;
	virtual void SetDepthFunc(CompareFunc func) = 0;
	virtual void SetCulling(CullMode mode) = 0;
	virtual void SetupSlopeZBias(bool enable, float slopeZBias, float depthOffset) = 0;

protected:
	virtual Shader* CreateShader(Shader::Type type, const char* name) = 0;
};