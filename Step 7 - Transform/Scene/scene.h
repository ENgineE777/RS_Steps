
#include "Helpers/Timer.h"
#include "Render/Render.h"

#include "plane.h"
#include "quad.h"

class Scene : public Object
{
public:

	Plane plane;
	Quad  quad;

	Texture* logo_tex;

	float  cam_angle;
	Matrix view;
	Matrix proj;

	void Init();
	void Render(float dt);
};
