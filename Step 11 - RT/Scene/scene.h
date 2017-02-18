
#include "Helpers/Timer.h"
#include "Render/Render.h"

#include "model.h"
#include "plane.h"
#include "quad.h"

class Scene : public Object
{
public:

	Model model;
	int num_drawers;
	Model::Drawer* model_drawers;

	Plane plane;
	Quad  quad;

	Texture* logo_tex;

	Texture* scene_rt;

	float  cam_angle;
	Matrix view;
	Matrix proj;

	void Init();
	void Render(float dt);
};
