
#pragma once

#include "Helpers/Helpers.h"

class Device
{
	friend class Render;

	virtual bool Init(int width, int height, void* data) = 0;
	virtual void Release() = 0;

public:
	virtual void Clear(bool renderTarget, Color color, bool zbuffer, float zValue) = 0;
	virtual void Present() = 0;
};