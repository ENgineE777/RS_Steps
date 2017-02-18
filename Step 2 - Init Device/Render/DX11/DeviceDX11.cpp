
#pragma once

#include "DeviceDX11.h"

DeviceDX11::DeviceDX11()
{
}

bool DeviceDX11::Init(int width, int height, void* data)
{
	return true;
}

void DeviceDX11::Clear(float r, float g, float b, float a)
{

}

void DeviceDX11::Release()
{
	delete this;
}