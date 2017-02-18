
#pragma once

#include "Render/Device.h"
#include "Render/Program.h"
#include <vector>
#include <map>

class Render
{
	friend class TextureDX11;

	Device* device;
	Matrix trans[4];
	bool   need_calc_trans;

	struct TextureRef
	{
		int count;
		Texture* texture;
	};

	std::map<std::string, TextureRef> textures;

public:

	enum Transform
	{
		World = 0,
		View = 1,
		Projection,
		WrldViewProj
	};

	Render();

	bool Init(const char* device, int width, int height, void* data);

	Device* GetDevice();

	void SetTransform(Transform trans, Matrix& mat);
	void GetTransform(Transform trans, Matrix& mat);

	Texture* LoadTexture(const char* name);

	void Execute(float dt);

	void Release();

protected:
	void CalcTrans();
	bool TexRefIsEmpty(Texture* texture);
};

extern Render render;