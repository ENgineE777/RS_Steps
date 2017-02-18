
#include "Helpers/Timer.h"
#include "Render/Render.h"

#include "quad.h"

class Scene : public Object
{
public:

	Quad  quad;

	Texture* logo_tex;

	void Init();
	void Render(float dt);
};
