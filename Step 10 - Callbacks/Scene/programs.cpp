
#include "programs.h"

Programs::TriangleProgram*   Programs::prg;
Programs::QuadProgram*       Programs::quad_prg;

void Programs::Init()
{
	prg = new TriangleProgram();
	prg->Init();

	quad_prg = new QuadProgram();
	quad_prg->Init();
}