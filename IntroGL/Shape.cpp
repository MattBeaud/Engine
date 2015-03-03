#include "Shape.h"

Shape::Shape(float in_x, float in_y, float in_width, float in_height, float in_U, float in_V, float in_UWidth, float in_VHeight) {
	x = in_x;
	y = in_y;
	width = in_width;
	height = in_height;
	U = in_U; 
	V = in_V;
	UWidth = in_UWidth;
	VHeight = in_VHeight;

	glGenBuffers(1, &vbo); //Generates a buffer BRUH
}

Shape::Shape()
{
	x = 0;
	y = 0;
	width = 10;
	height = 10;
	U = 0;
	V = 0;
	UWidth = 0;
	VHeight = 0;




	glGenBuffers(1, &vbo); //Generates a buffer BRUH


}

void Shape::syncVbo() 
{
	float vertices[] =
	{
		//  Position                 Color               Texcoords
		x, y,                  1.0f, 1.0f, 1.0f, 1.0f, U, V + VHeight,  // Top-left
		x + width, y,          1.0f, 1.0f, 1.0f, 1.0f, U + UWidth, V + VHeight,  // Top-right
		x + width, y + height, 1.0f, 1.0f, 1.0f, 1.0f, U + UWidth, V,  // Bottom-right
		x, y + height,         1.0f, 1.0f, 1.0f, 1.0f, U, V,  // Bottom-left
	

	};


	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
void Shape::Draw()
{
	

	// Draw a triangle from the 3 vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Shape::~Shape()
{
}

