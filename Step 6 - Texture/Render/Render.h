
#pragma once

#include "Render/Device.h"
#include "Render/Program.h"
#include <vector>
#include <map>

class Render
{
	friend class TextureDX11;

	Device* device;

	struct TextureRef
	{
		int count;
		Texture* texture;
	};

	std::map<std::string, TextureRef> textures;

public:

	Render();

	bool Init(const char* device, int width, int height, void* data);

	Device* GetDevice();

	Texture* LoadTexture(const char* name);

	void Execute(float dt);

	void Release();

protected:
	bool TexRefIsEmpty(Texture* texture);
};

extern Render render;