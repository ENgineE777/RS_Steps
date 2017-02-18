
#include "programs.h"

Programs::QuadProgram*       Programs::quad_prg;

void Programs::Init()
{
	quad_prg = new QuadProgram();
	quad_prg->Init();
}