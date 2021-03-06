
#include "Plane.h"
#include "programs.h"

void Plane::Init(float plane_y, const char* tex_name)
{
	int stride = sizeof(VertexTri);
	buffer = render.GetDevice()->CreateBuffer(stride * 6, stride);

	VertexTri* v_tri = (VertexTri*)buffer->Lock();

	float plane_size = 75.0f;
	float plane_tiling = plane_size * 0.3f;

	v_tri[0].position = Vector(-plane_size, plane_y, plane_size);
	v_tri[0].texCoord = Vector2(0.0f, 0.0f);
	v_tri[1].position = Vector(plane_size, plane_y, plane_size);
	v_tri[1].texCoord = Vector2(plane_tiling, 0.0f);
	v_tri[2].position = Vector(plane_size, plane_y, -plane_size);
	v_tri[2].texCoord = Vector2(plane_tiling, plane_tiling);

	v_tri[3].position = Vector(-plane_size, plane_y, plane_size);
	v_tri[3].texCoord = Vector2(0.0f, 0.0f);
	v_tri[4].position = Vector(plane_size, plane_y, -plane_size);
	v_tri[4].texCoord = Vector2(plane_tiling, plane_tiling);
	v_tri[5].position = Vector(-plane_size, plane_y, -plane_size);
	v_tri[5].texCoord = Vector2(0.0f, plane_tiling);

	buffer->Unlock();

	texture = render.LoadTexture("Media//grass.tga");
}

void Plane::Render()
{
	render.GetDevice()->SetVertexBuffer(0, buffer);

	Programs::prg->Apply();

	Vector4 color(1.0f, 1.0f, 1.0f, 1.0f);

	render.SetTransform(Render::World, Matrix());

	Matrix trans;
	render.GetTransform(Render::WrldViewProj, trans);

	Matrix mat;
	Programs::prg->VS_SetMatrix("trans", &trans, 1);
	Programs::prg->PS_SetVector("color", &color, 1);
	Programs::prg->PS_SetTexture("diffuseMap", texture);

	render.GetDevice()->Draw(Device::TrianglesList, 0, 2);
}