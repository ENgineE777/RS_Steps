#include "Scene.h"

void Scene::Init()
{
	quad.Init();

	plane.Init(0.0f, "Media//grass.tga");

	logo_tex = render.LoadTexture("Media//logo.tga");

	cam_angle = 0;
	proj.BuildProjection(45.0f * RADIAN, 600.0f / 800.0f, 1.0f, 100.0f);
}

void Scene::Render(float dt)
{
	cam_angle -= 60 * RADIAN * dt * 0.5f;

	float r = 20;
	view.BuildView(Vector(cosf(cam_angle) * r, 10, sinf(cam_angle) * r), Vector(0.0f, 3.0f, 0.0f), Vector(0, 1, 0));

	render.GetDevice()->Clear(true, COLOR_LIGHT_GRAY, true, 1.0f);

	render.SetTransform(Render::View, view);
	render.SetTransform(Render::Projection, proj);

	plane.Render();

	quad.Draw(logo_tex, Vector2(10.0f), Vector2(100.0f));

	render.GetDevice()->Present();
}
