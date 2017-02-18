
#pragma once

#include "Helpers/Helpers.h"

class Shader
{	
public:
	enum Type
	{
		Vertex = 0,
		Pixel  = 1
	};

	Shader(Type tp) { sdr_type = tp; };

	virtual bool SetVector(const char* param, Vector4* v, int count) = 0;
	virtual bool SetMatrix(const char* param, Matrix* m, int count) = 0;

	virtual void UpdateConstants() = 0;

	virtual void Apply() = 0;
	virtual void Release() = 0;

protected:
	Type sdr_type;
};