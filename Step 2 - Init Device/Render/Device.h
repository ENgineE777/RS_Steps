
#pragma once

#include "Helpers/Timer.h"

class Device
{
	friend class Render;

	virtual bool Init(int width, int height, void* data) = 0;
	virtual void Release() = 0;

public:
	virtual void Clear(float r, float g, float b, float a) = 0;
};