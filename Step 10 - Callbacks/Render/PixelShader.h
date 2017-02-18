
#pragma once

#include "Core/Render/Textures/Texture.h"

#include "Shader.h"

class PixelShader : public Shader
{	
public:

	PixelShader(const char* file) : Shader(file) {};
	
	virtual ~PixelShader() {};
	virtual bool SetTexture(const char* param, Texture* tex) { return true; };		   	
	virtual bool SetTexture(const char* param, int slot, Texture* tex) { return true; };		   	
	virtual void UpdateTextures() {};
};
