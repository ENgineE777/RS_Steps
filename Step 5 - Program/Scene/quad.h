
#include "Helpers/Timer.h"
#include "Render/Render.h"

class Quad
{
public:

	GeometryBuffer* buffer;

	void Init();
	void Draw(Vector2 pos, Vector2 size);
};
