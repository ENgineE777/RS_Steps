
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

Texture* Render::LoadTexture(const char* name)
{
	if (textures.count(name) > 0)
	{
		TextureRef& ref = textures[name];

		ref.count++;
		return ref.texture;
	}

	Buffer buffer(name);

	uint8_t* ptr = buffer.GetData();

	if (!ptr)
	{
		return NULL;
	}

	ptr += 2;

	uint8_t imageTypeCode = *((uint8_t*)ptr);

	if (imageTypeCode != 2 && imageTypeCode != 3)
	{
		return NULL;
	}

	ptr += 10;

	short int imageWidth = *((short int*)ptr);
	ptr += 2;

	short int imageHeight = *((short int*)ptr);
	ptr += 2;

	uint8_t bitCount = *((uint8_t*)ptr);
	ptr += 2;

	int colorMode = bitCount / 8;

	Texture* texture = device->CreateTexture(imageWidth, imageHeight, Texture::FMT_A8R8G8B8, 0, false, Texture::Tex2D);

	int pitch;
	int pitchSlice;

	uint8_t* dest = (uint8_t*)malloc(imageWidth * imageHeight * 4);

	for (int j = 0; j < imageHeight; j++)
	{
		if (colorMode == 4)
		{
			for (int i = 0; i < imageWidth; i++)
			{
				uint8_t* dst = &dest[((imageHeight - 1 - j) * imageWidth + i) * 4];
				memcpy(dst, &ptr[(j * imageWidth + i) * 4], 4);
				uint8_t tmp = dst[0];
				dst[0] = dst[2];
				dst[2] = tmp;
			}
		}
		else
		if (colorMode == 3)
		{
			for (int i = 0; i < imageWidth; i++)
			{
				uint8_t* dst = &dest[((imageHeight - 1 - j) * imageWidth + i) * 4];
				memcpy(dst, &ptr[(j * imageWidth + i) * 3], 3);
				uint8_t tmp = dst[0];
				dst[0] = dst[2];
				dst[2] = tmp;

				dst[3] = 255;
			}
		}
	}

	texture->Update(0, 0, dest, imageWidth * 4);

	free(dest);

	texture->GenerateMips();

	TextureRef& ref = textures[name];

	ref.count = 1;
	ref.texture = texture;

	return texture;
}

bool Render::TexRefIsEmpty(Texture* texture)
{
	typedef std::map<std::string, TextureRef>::iterator it_type;

	for (it_type iterator = textures.begin(); iterator != textures.end(); iterator++)
	{
		if (iterator->second.texture == texture)
		{
			iterator->second.count--;

			if (iterator->second.count == 0)
			{
				textures.erase(iterator);
				return true;
			}

			return false;
		}
	}

	return true;
}

void Render::Release()
{
	device->Release();
}