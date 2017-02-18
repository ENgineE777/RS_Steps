#include "Scene.h"

void Scene::Init()
{
	quad.Init();

	logo_tex = render.LoadTexture("Media//logo.tga");
}

void Scene::Render(float dt)
{
	render.GetDevice()->Clear(true, COLOR_LIGHT_GRAY, true, 1.0f);

	quad.Draw(logo_tex, Vector2(10.0f), Vector2(100.0f));

	render.GetDevice()->Present();
}
