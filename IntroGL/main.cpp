#include <GL/glew.h>
#include <GL/wglew.h>
#include <SOIL.h>

//GLEW includes must come before anything else
#include <vector>
#include <string>
#include <fstream>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ctime>
#include <iostream>
#include <tinyxml2.h>

#include "Shape.h"
#include "Animator.h"

const GLchar* vertexSource =

"#version 330\n"
"in vec2 position;"
"in vec4 color;"
"in vec2 texcoord;"
"out vec4 Color;"
"out vec2 Texcoord;"
"uniform mat4 trans;"
"void main()"
"{"
"	Texcoord = texcoord;"
"	Color = color;"
"   gl_Position = vec4(position, 0.0, 1.0);"
"}";

const GLchar* fragmentSource =
"#version 330\n"
"in vec4 Color;"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex;"
"void main() "
"{"
"outColor = texture(tex, Texcoord) * Color;"
//"   outColor = texture(texSonic, Texcoord) * vec4(Color, 1.0);"
"}";






int main()
{
	

	//initilization of GLFW
	if (!glfwInit())
	{
		return -1;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "ENGINE", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//Make windows context Current
	glfwMakeContextCurrent(window);

	//------------------------------------------------------------------
	//Start GLEW
	if (glewInit() != GLEW_OK)
	{
		//OpenGL didn't Start-up! shutdown GLFW and return an error
		fprintf(stderr, "ERROR: GLFW was not started");
		glfwTerminate();
		return -1;
	}
	//------------------------------------------------------------------
	//Loop until user closes the window


	


	//Generate Shaders
//Vertex
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	//TEST
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

	if (status == GL_TRUE)
	{
		printf("Vertex shader compiled successfully\n");
		
	}
	else if (status == GL_FALSE)
	{
		printf("Vertex shader error.\n");
	}
	char buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

	printf(buffer);

//FRAGMENT
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	//TEST(SHIT)
	GLint SHIT;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &SHIT);

	if (SHIT == GL_TRUE)
	{
		printf("Fragment shader working \n");
	}
	else if (SHIT == GL_FALSE)
	{
		printf("Fragment shader error.\n");

	}

	// SHADER PROGRAM
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	//Linksshaders
	glLinkProgram(shaderProgram);
	//start using shit
	glUseProgram(shaderProgram);
	
	//layout of vertex data
	Shape triangle = Shape(-0.5, -0.5, 0.5, 0.5, 0, 0, 0.09, 0.09, shaderProgram, "MegamanxSheet.png");
	triangle.syncVbo();
	triangle.syncEbo();
	triangle.Texturing();

	//Animator animator = Animator();
	//animator.LoadSprite;

	//animator.LoadSprite("MegamanXSheet.xml");

	while (!glfwWindowShouldClose(window))
	{
		{
			// Clear the screen to black
			glClearColor(0.8f, 0.0f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						
			triangle.Draw();
			
			//glDrawArrays(GL_TRIANGLES, 0, 3);

			//swap front and back buffers
			glfwSwapBuffers(window);
		}
		//poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

