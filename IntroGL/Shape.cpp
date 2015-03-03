#include "Shape.h"

Shape::Shape(float in_x, float in_y, float in_width, float in_height, float in_U, float in_V, float in_UWidth, float in_VHeight, GLuint in_shaderProgram) : Shape() {
	x = in_x;
	y = in_y;
	width = in_width;
	height = in_height;
	U = in_U; 
	V = in_V;
	UWidth = in_UWidth;
	VHeight = in_VHeight;
	shaderProgram = in_shaderProgram;

	// Specify vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");

	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(texAttrib);
	glEnableVertexAttribArray(colAttrib);

	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(2 * sizeof(float)));
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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
	glGenBuffers(1, &ebo);
	glGenTextures(2, textures);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
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

void Shape::syncEbo()
{
	GLuint elements[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}


void Shape::Texturing()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	int width, height;
	unsigned char* image = SOIL_load_image("MegaManXSheet.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glUniform1i(glGetUniformLocation(shaderProgram, "tex"), 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}


void Shape::Draw()
{
	
	// Draw a triangle from the 3 vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Shape::~Shape()
{
}

