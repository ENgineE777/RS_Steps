#include <windows.h>

#include "Helpers/Timer.h"
#include "Render/Render.h"

class Programs
{
public:

	class QuadProgram : public Program
	{
	public:
		virtual const char* GetVsName() { return "shaders//screen_vs.shd"; };
		virtual const char* GetPsName() { return "shaders//screen_ps.shd"; };

		virtual void Apply()
		{
			Program::Apply();
		};
	};

	static QuadProgram*       quad_prg;

	static void Init();
};
