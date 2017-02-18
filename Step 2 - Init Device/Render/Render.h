
#pragma once

#include "Render/Device.h"

class Render
{
	Device* device;

public:
	Render();

	bool Init(const char* device, int width, int height, void* data);
	
	Device* GetDevice();

	void Release();
};

extern Render render;