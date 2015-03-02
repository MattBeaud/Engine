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


#include "Shape.h"

const GLchar* vertexSource =

"#version 330\n"
"in vec2 position;"
"void main() {"
"   gl_Position = vec4(position, 0.0, 1.0);"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
"out vec4 outColor;"
"void main() {"
"   outColor = vec4(1.0, 1.0, 1.0, 1.0);"
"}";












int main()
{
	
	//initilization of GLFW
	if (!glfwInit())
	{
		return -1;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Butts bruh", NULL, NULL);

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


	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


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
	//glBindFragDataLocation(shaderProgram, 0, "outColor");
	//Linksshaders
	glLinkProgram(shaderProgram);
	//start using shit
	glUseProgram(shaderProgram);
	
	//layout of vertex data
	Shape triangle = Shape(1, 1, 1, 1);
	triangle.syncVbo();
	glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);




	while (!glfwWindowShouldClose(window))
	{
		{
			// Clear the screen to black
			glClearColor(0.2f, 0.4f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw a triangle from the 3 vertices
			glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

// test commit, please ignore