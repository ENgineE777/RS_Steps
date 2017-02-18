
#include "programs.h"

Programs::TriangleProgram*   Programs::prg;
Programs::ShTriangleProgram* Programs::shprg;
Programs::ColorProgram*      Programs::color_prg;
Programs::QuadProgram*       Programs::quad_prg;

void Programs::Init()
{
	prg = new TriangleProgram();
	prg->Init();

	shprg = new ShTriangleProgram();
	shprg->Init();

	color_prg = new ColorProgram();
	color_prg->Init();

	quad_prg = new QuadProgram();
	quad_prg->Init();
}