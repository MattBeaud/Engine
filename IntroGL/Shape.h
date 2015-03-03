#ifndef _Shape_h_
#define _Shape_h_
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SOIL.h>
//GLEW includes must come before anything else
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <GL/glew.h>


class Shape
{

public:
	Shape(float in_x, float in_y, float in_width, float in_height, float in_U, float in_V, float in_UWidth, float in_VHeight);
	Shape();
	~Shape();

	void syncVbo();
	void Draw();
	//float vertices; // holy fucking shit
	float x;
	float y;
	float width;
	float height;
	float U;
	float V;
	float UWidth;
	float VHeight;
	
	GLuint vbo;
	GLuint ebo;	// todo
	GLuint vao;	// todo if time allows or justin mandates

	GLuint shaderProgram;	// todo
};

#endif

