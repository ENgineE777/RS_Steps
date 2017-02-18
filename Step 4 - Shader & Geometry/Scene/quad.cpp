#include "Quad.h"

void Quad::Init()
{
	int stride = sizeof(Vector2);
	buffer = render.GetDevice()->CreateBuffer(stride * 4, stride);

	Vector2* v = (Vector2*)buffer->Lock();

	v[0] = Vector2(0, 0);
	v[1] = Vector2(1, 0);
	v[2] = Vector2(0, 1);
	v[3] = Vector2(1, 1);

	buffer->Unlock();

	vshader = render.GetDevice()->CreateShader(Shader::Vertex, "shaders//screen_vs.shd");
	pshader = render.GetDevice()->CreateShader(Shader::Pixel, "shaders//screen_ps.shd");
}

void Quad::Draw(Vector2 pos, Vector2 size)
{
	render.GetDevice()->SetVertexBuffer(0, buffer);

	vshader->Apply();
	pshader->Apply();

	Vector4 params[3];
	params[0] = Vector4(pos.x, pos.y, size.x, size.y);
	params[1] = Vector4(800, 600, 0.5f, 0);
	params[2] = Vector4(1.0f, 1.0f, 1.0f, 1);

	vshader->SetVector("desc", &params[0], 2);
	pshader->SetVector("color", &params[2], 1);

	vshader->UpdateConstants();
	pshader->UpdateConstants();

	render.GetDevice()->Draw(Device::TriangleStrip, 0, 2);
}