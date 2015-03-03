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

struct AniSprite
{
	std::string Name;
	float width, height;
	float x0, x1, y0, y1;
};

AniSprite testSprite;

void LoadSprites(const char* a_pAnimationSheet)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement, *child;
	std::string str, aniName;
	doc.LoadFile(a_pAnimationSheet); // load the document
	rootNode = doc.FirstChildElement("atlas");// set the root node
	currentNode = rootNode->FirstChildElement("sprite");
	
	

	for (childElement = currentNode->ToElement();
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		aniName = childElement->Attribute("name");
		int i = childElement->IntAttribute("x0");
		int ii = childElement->IntAttribute("x1");

		for (child = childElement->FirstChildElement();
			child != NULL; child = child->NextSiblingElement())
		{
			str = child->Attribute("name");
			int x0 = child->IntAttribute("x0");
			//mAnimations[aniName].push_back(str);
			i++;
		}
	}
std:printf("Animation load done!\n");

}

int main()
{
	LoadSprites("MegamanXSheet.xml");

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
	Shape triangle = Shape(-0.5, -0.5, 1, 1, 0, 0, 0.082, 0.3, shaderProgram, "MegamanxSheet.png");
	triangle.syncVbo();
	triangle.syncEbo();
	triangle.Texturing();

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

