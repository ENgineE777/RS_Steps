
#pragma once

#include "Helpers/Helpers.h"
#include "Shader.h"
#include "GeometryBuffer.h"

class Device
{
	friend class Render;
	friend class Program;

	virtual bool Init(int width, int height, void* data) = 0;
	virtual void Release() = 0;

public:

	struct Rect
	{
		short left;
		short right;
		short top;
		short bottom;
	};

	enum Primitive
	{
		LineStrip = 0,
		LinesList,
		TriangleStrip,
		TrianglesList
	};

	virtual void Clear(bool renderTarget, Color color, bool zbuffer, float zValue) = 0;
	virtual void Present() = 0;

	virtual GeometryBuffer* CreateBuffer(int size, int stride) = 0;
	virtual void SetVertexBuffer(int slot, GeometryBuffer* buffer) = 0;

	virtual void Draw(Primitive prim, int startVertex, int primCount) = 0;

	virtual Shader* CreateShader(Shader::Type type, const char* name) = 0;
};