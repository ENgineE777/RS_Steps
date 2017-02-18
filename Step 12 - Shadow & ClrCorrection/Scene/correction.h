
#include "Helpers/Timer.h"
#include "Render/Render.h"

class ColorCorrection
{
public:

	GeometryBuffer* buffer;

	void Init();
	void Draw(Texture* rt);
};
