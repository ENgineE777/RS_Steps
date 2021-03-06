
#include "Helpers/Timer.h"
#include "Render/Render.h"

class Model
{
public:

	class Drawer : public Object
	{
		Model* res;
		Matrix world;
		Vector4 color;

	public:
		Drawer()
		{
			res = NULL;
			color = 1.0f;
		};

		void Init(Model* model);
		void SetColor(Vector4& color);
		void SetPosition(Vector2 pos);

		void Render();
	};

	struct ModelVertex
	{
		Vector  pos;
		Vector2 uv;
		Vector  normal;
	};

	struct Mesh
	{
		int texture;
		int num_triangles;
		GeometryBuffer* buffer;
	};

	Vector bb_max;
	Vector bb_min;

	std::vector<Texture*> textures;
	std::vector<Mesh> meshes;

	void LoadModelMS3D(const char* filename);
};