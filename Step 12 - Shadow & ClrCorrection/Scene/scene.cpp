#include "Scene.h"

void Scene::Init()
{
	quad.Init();

	plane.Init(0.0f, "Media//grass.tga");

	correction.Init();

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

	shadow = render.GetDevice()->CreateTexture(1024, 1024, Texture::FMT_D16, 1, true, Texture::Tex2D);

	scene_rt = render.GetDevice()->CreateTexture(800, 600, Texture::FMT_A8R8G8B8, 1, true, Texture::Tex2D);
	scene_depth = render.GetDevice()->CreateTexture(800, 600, Texture::FMT_D16, 1, true, Texture::Tex2D);

	cam_angle = 0;
	light_proj.BuildProjection(45.0f * RADIAN, 1.0f, 1.0f, 100.0f);
	proj.BuildProjection(45.0f * RADIAN, 600.0f / 800.0f, 1.0f, 100.0f);

	render.AddDelegate("prepare", this, (Object::Delegate)&Scene::RenderPrepare, 0);
	render.AddDelegate("main", this, (Object::Delegate)&Scene::Render, 0);
}

void Scene::RenderPrepare(float dt)
{
	cam_angle -= 60 * RADIAN * dt * 0.5f;

	float r = 25;
	light_view.BuildView(Vector(cosf(-cam_angle) * r, r, sinf(-cam_angle) * r), 0.0f, Vector(0, 1, 0));

	r = 20;
	view.BuildView(Vector(cosf(cam_angle) * r, 10, sinf(cam_angle) * r), Vector(0.0f, 3.0f, 0.0f), Vector(0, 1, 0));

	Matrix light_view_proj = light_view * light_proj;

	Program::SetMatrix("sh_trans", &light_view_proj);
	Program::SetTexture("shdMap", shadow);
}

void Scene::RenderToShadow(float dt)
{
	render.GetDevice()->SetRenderTarget(0, NULL);
	render.GetDevice()->SetDepth(shadow);

	render.GetDevice()->Clear(true, COLOR_WHITE, true, 1.0f);

	render.GetDevice()->SetupSlopeZBias(true, 0.5f, 0.5f);

	render.SetTransform(Render::View, light_view);
	render.SetTransform(Render::Projection, light_proj);

	render.ExecuteDelgateList("toshadow", dt);

	render.GetDevice()->SetupSlopeZBias(false, 0.001f, 0.001f);

	render.GetDevice()->RestoreRenderTarget();
}

void Scene::RenderScene(const char* phase, float dt)
{
	render.GetDevice()->SetRenderTarget(0, scene_rt);
	render.GetDevice()->SetDepth(scene_depth);

	render.GetDevice()->Clear(true, COLOR_LIGHT_GRAY, true, 1.0f);

	render.SetTransform(Render::View, view);
	render.SetTransform(Render::Projection, proj);

	render.ExecuteDelgateList(phase, dt);

	render.GetDevice()->RestoreRenderTarget();
}

void Scene::RenderCorrection(float dt)
{
	render.GetDevice()->Clear(true, COLOR_GRAY, true, 1.0f);

	correction.Draw(scene_rt);

	quad.Draw(logo_tex, Vector2(10.0f, 10.0f), Vector2(150.0f));
}

void Scene::Render(float dt)
{
	RenderToShadow(dt);
	RenderScene("shgeometry", dt);

	RenderCorrection(dt);

	render.GetDevice()->Present();
}
