
#pragma once

#include "Helpers/Timer.h"
#include "Render/Device.h"

class DeviceDX11 : public Device
{
	friend class Render;

	DeviceDX11();
	virtual bool Init(int width, int height, void* data);
	virtual void Release();

public:
	virtual void Clear(float r, float g, float b, float a);
};