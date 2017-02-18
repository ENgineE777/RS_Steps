#include "correction.h"
#include "programs.h"

void ColorCorrection::Init()
{
	int stride = sizeof(Vector2);
	buffer = render.GetDevice()->CreateBuffer(stride * 4, stride);

	Vector2* v = (Vector2*)buffer->Lock();

	v[0] = Vector2(-1, -1);
	v[1] = Vector2(1, -1);
	v[2] = Vector2(-1, 1);
	v[3] = Vector2(1, 1);

	buffer->Unlock();
}

void ColorCorrection::Draw(Texture* rt)
{
	render.GetDevice()->SetVertexBuffer(0, buffer);

	Programs::color_prg->Apply();
	Programs::color_prg->PS_SetTexture("rt", rt);

	render.GetDevice()->Draw(Device::TriangleStrip, 0, 2);
}