
#pragma once

#include "Helpers/Helpers.h"

class GeometryBuffer
{	
protected:

	int size;
	int stride;

public:

	enum ElemType
	{
		float2 = 0,
		float3,
		float4,
		tp_color,
		ubyte4,
		short4,
		dec4,
		short2
	};

	enum ElemUsage
	{
		position = 0,
		positiont,
		normal,
		texcoord,
		color,
		binormal,
		tangent,
		blendindex,
		blendweight
	};

	GeometryBuffer(int sz, int strd) { size = sz; stride = strd; };
	virtual ~GeometryBuffer() {};

	virtual void StartDesc() = 0;
	virtual void AddDescElem(ElemUsage usage, ElemType type, const char* name) = 0;
	virtual void EndDesc() = 0;

	virtual void* Lock() = 0;
	virtual void Unlock() = 0;
	virtual void* GetData() = 0;
	int GetSize() { return size; };
	int GetStride() { return stride; };
	virtual void Release() = 0;
};
