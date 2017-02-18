#include "Scene.h"

void Scene::Init()
{
	quad.Init();

	plane.Init(0.0f, "Media//grass.tga");

	model.LoadModelMS3D("Media//odst.ms3d");

	num_drawers = 15;
	model_drawers = new Model::Drawer[num_drawers];

	for (int i = 0; i < num_drawers; i++)
	{
		model_drawers[i].Init(&model);

		Vector2 pos(rnd_range(-7.5f, 7.5f), rnd_range(-7.5f, 7.5f));
		model_drawers[i].SetPosition(pos);

		Vector4 color(rnd_range(0.5f, 1.0f), rnd_range(0.5f, 1.0f), rnd_range(0.5f, 1.0f));
		model_drawers[i].SetColor(color);
	}

	logo_tex = render.LoadTexture("Media//logo.tga");

	scene_rt = render.GetDevice()->CreateTexture(800, 600, Texture::FMT_A8R8G8B8, 1, true, Texture::Tex2D);

	cam_angle = 0;
	proj.BuildProjection(45.0f * RADIAN, 600.0f / 800.0f, 1.0f, 100.0f);

	render.AddDelegate("main", this, (Object::Delegate)&Scene::Render, 0);
}

void Scene::Render(float dt)
{
	cam_angle -= 60 * RADIAN * dt * 0.5f;

	float r = 20;
	view.BuildView(Vector(cosf(cam_angle) * r, 10, sinf(cam_angle) * r), Vector(0.0f, 3.0f, 0.0f), Vector(0, 1, 0));

	render.GetDevice()->SetRenderTarget(0, scene_rt);

	render.GetDevice()->Clear(true, COLOR_LIGHT_GRAY, true, 1.0f);

	render.SetTransform(Render::View, view);
	render.SetTransform(Render::Projection, proj);

	render.ExecuteDelgateList("geometry", dt);

	render.GetDevice()->RestoreRenderTarget();

	quad.Draw(scene_rt, Vector2(0.0f), Vector2(400, 600));
	quad.Draw(scene_rt, Vector2(400, 0.0f), Vector2(400, 600));
	quad.Draw(logo_tex, Vector2(10.0f), Vector2(100.0f));

	render.GetDevice()->Present();
}
