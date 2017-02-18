#include <windows.h>

#include "Helpers/Timer.h"
#include "Render/Render.h"

class Programs
{
public:

	class TriangleProgram : public Program
	{
	public:
		virtual const char* GetVsName() { return "shaders//triangle_vs.shd"; };
		virtual const char* GetPsName() { return "shaders//triangle_ps.shd"; };

		virtual void Apply()
		{
			Program::Apply();
			render.GetDevice()->SetAlphaBlend(false);
			render.GetDevice()->SetDepthWriting(true);
		};
	};

	class QuadProgram : public Program
	{
	public:
		virtual const char* GetVsName() { return "shaders//screen_vs.shd"; };
		virtual const char* GetPsName() { return "shaders//screen_ps.shd"; };

		virtual void Apply()
		{
			Program::Apply();
			render.GetDevice()->SetAlphaBlend(true);
			render.GetDevice()->SetDepthWriting(false);
		};
	};

	static QuadProgram*       quad_prg;
	static TriangleProgram*   prg;

	static void Init();
};
