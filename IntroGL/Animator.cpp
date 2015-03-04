#include <GL/glew.h>
#include <GL/wglew.h>
#include <SOIL.h>

#include "Animator.h"
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



Animator::Animator()
{
}


Animator::~Animator()
{
}


void Animator::LoadSprite(const char* a_pSpriteSheet)
{
	//tinyxml2::XMLDocument doc;
	//tinyxml2::XMLNode *rootNode, *currentNode;
	//tinyxml2::XMLElement *childElement;
	//std::string str;
	//doc.LoadFile(a_pSpriteSheet); // load the document
	//rootNode = doc.FirstChildElement("atlas");// set the root node
	//currentNode = rootNode;


}

void Animator::LoadAnimations(const char* a_pAnimationSheet)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement, *child;
	std::string str, aniName;
	doc.LoadFile(a_pAnimationSheet); // load the document
	rootNode = doc.FirstChildElement("animation");// set the root node
	currentNode = rootNode;



	for (childElement = currentNode->ToElement();
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		aniName = childElement->Attribute("name");
		int i = 0;
		/*int ii = childElement->IntAttribute("x1");
		int iii = childElement->IntAttribute("y0");
		int iiii = childElement->IntAttribute("y1");*/

		for (child = childElement->FirstChildElement();
			child != NULL; child = child->NextSiblingElement())
		{
			str = child->Attribute("name");
			//mAnimations[aniName].push_back(str);
			i++;
		}
	}
std:printf("Animation load done!\n");
}