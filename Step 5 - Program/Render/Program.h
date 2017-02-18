
#pragma once

#include "Shader.h"
#include <map>

class Program
{
protected:
	Shader* vshader;
	Shader* pshader;

	friend class Device;

	static Program* current;
	static int      set_stage;
	void SetShaders();

	static std::map<std::string, Vector4>  vectors;
	static std::map<std::string, Matrix>   matrixes;

public:	

	Program();
	virtual ~Program() {};
	virtual bool Init();

	virtual const char* GetVsName() = 0;
	virtual const char* GetPsName() = 0;

	virtual void Apply();

	static void SetVector(const char* param, Vector4* v);
	static void SetMatrix(const char* param, Matrix* mat);

	virtual void VS_SetVector(const char* param, Vector4* v, int count);
	virtual void VS_SetMatrix(const char* param, Matrix* mat, int count);

	virtual void PS_SetVector(const char* param, Vector4* v, int count);
	virtual void PS_SetMatrix(const char* param, Matrix* mat, int count);
};