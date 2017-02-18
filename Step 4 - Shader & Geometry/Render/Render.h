
#pragma once

#include "Render/Device.h"
#include <vector>
#include <map>

class Render
{
	friend class TextureDX11;

	Device* device;

public:

	Render();

	bool Init(const char* device, int width, int height, void* data);

	Device* GetDevice();

	void Release();
};

extern Render render;