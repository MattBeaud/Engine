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
"in vec3 color;"
"in vec2 texcoord;"

"out vec3 Color;"
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
"in vec3 Color;"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex;"
"void main() "
"{"
"   outColor = texture(tex, Texcoord) * vec4(Color, 1.0);"
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

	
//---------------------------------------------------------------------------------
	//LOAD TEXTURE
	GLuint tex;
	glGenTextures(1, &tex);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	int width, height;
	unsigned char* image =
		SOIL_load_image("Sonic.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);




	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Retrieving Postion
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");


	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(texAttrib);
	glEnableVertexAttribArray(colAttrib);


	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));







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