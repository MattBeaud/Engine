#include "Shape.h"

Shape::Shape(float in_x, float in_y, float in_width, float in_height) {
	x = in_x;
	y = in_y;
	width = in_width;
	height = in_height;

	glGenBuffers(1, &vbo); //Generates a buffer BRUH
}

Shape::Shape()
{
	x = 0;
	y = 0;
	width = 10;
	height = 10;

	glGenBuffers(1, &vbo); //Generates a buffer BRUH

}

void Shape::syncVbo() {
	float vertices[] =
	{
		//  Position      Color           Texcoords
		-0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
		0.5f,   0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
		0.5f,  -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // Bottom-left
	};


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}


Shape::~Shape()
{
}

