
#include "Render.h"

#include "Render.h"
#include "DX11/DeviceDX11.h"
#include <memory>

Render render;

Render::Render()
{
	device = NULL;
}

bool Render::Init(const char* device_name, int width, int height, void* data)
{
	device = new DeviceDX11();

	return device->Init(width, height, data);
}

Device* Render::GetDevice()
{
	return device;
}

void Render::Release()
{
	device->Release();
}