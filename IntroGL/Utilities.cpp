#include "Utilities.h"

int g_gl_width = 640;
int g_gl_height = 480;
double deltaTime = 0;
int frames;
double fps, elapsedTime;
//Utilities::Utilities()
//{
//}
//
//
//Utilities::~Utilities()
//{
//}


double getDeltaTime()
{
	return deltaTime;
}
void resetDeltaTime()
{

	deltaTime = glfwGetTime();
	elapsedTime += deltaTime;
	frames++;
	if (elapsedTime > 0.25)
	{
		fps = (double)frames / elapsedTime;
		elapsedTime = 0;
		frames = 0;
	}
	glfwSetTime(0);

}