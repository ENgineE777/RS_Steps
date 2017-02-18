
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

	struct DelegateList
	{
		char name[32];
		std::vector<DelegateObject> list;
	};

	std::vector<DelegateList> delegateList;

	struct ExecutedDelegateList
	{
		int  level;
		char name[32];
		DelegateList* list;
	};

	std::vector<ExecutedDelegateList> executedDelegateLists;

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

	void AddExecutedDelgateList(const char* list_name, int level);
	void ExecuteDelgateList(const char* list_name, float dt);

	void AddDelegate(const char* list_name, Object* entity, Object::Delegate call, int level);
	void DelDelegate(const char* list_name, Object* entity);
	void DelAllDelegates(Object* entity);

	void Release();

protected:
	void CalcTrans();
	bool TexRefIsEmpty(Texture* texture);
	DelegateList* FindExecuteList(const char* list_name);
};

extern Render render;