#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" 
#include "GLFW/glfw3.h"
//class Utilities
//{
//public:
//	Utilities();
//	~Utilities();
//};

struct float2
{
	float2(){}
	float2(float a_u, float a_v)
	{
		U = a_u;
		V = a_v;
	}
	float U, V;
};

enum PlayType
{
	ONCE,
	LOOP,
	LOOPSECTION,
	PINGPONG,
	REVERSE,
	RANDOMLOOP,
	RANDOM,
	SINGLE
};

double getDeltaTime();
void resetDeltaTime();