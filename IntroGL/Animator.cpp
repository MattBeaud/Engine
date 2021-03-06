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




void Animator::Initialize(Shape * shape, glm::vec2 &Scale)
{
	U = &shape->U;
	V = &shape->V;
	UWidth = &shape->UWidth;
	VHeight = &shape->VHeight;

	m_SpriteScale = &Scale;
}

void Animator::ImportSheet(const char* a_pSpriteSheet)
{
	LoadSprite(a_pSpriteSheet);
	LoadAnimations(atlas.sAnimations.c_str());

	m_dFrames = (1.0 / 15.0);
	currentAnimation = "";
	currentSprite = "idle";
	currentFrame = 0;
	currentPlayType = SINGLE;
	SetSprite();
}

void Animator::SetSprite()
{
	if (currentAnimation == "")
	{
		*U = mSprites["idle"].x0 / atlas.width;
		*V = mSprites["idle"].y0 / atlas.height;
		*U = mSprites["idle"].x1 / atlas.width;
		*V = mSprites["idle"].y0 / atlas.height;
		*U = mSprites["idle"].x0 / atlas.width;
		*V = mSprites["idle"].y1 / atlas.height;
		*U = mSprites["idle"].x1 / atlas.width;
		*V = mSprites["idle"].y1 / atlas.height;

		m_SpriteScale->x = mSprites[currentSprite].width;
		m_SpriteScale->y = mSprites[currentSprite].height;
	}
	else
	{

		*U = mSprites[currentSprite].x0 / atlas.width;
		*V = mSprites[currentSprite].y0 / atlas.height;
		*U = mSprites[currentSprite].x1 / atlas.width;
		*V = mSprites[currentSprite].y0 / atlas.height;
		*U = mSprites[currentSprite].x0 / atlas.width;
		*V = mSprites[currentSprite].y1 / atlas.height;
		*U = mSprites[currentSprite].x1 / atlas.width;
		*V = mSprites[currentSprite].y1 / atlas.height;

		m_SpriteScale->x = mSprites[currentSprite].width;
		m_SpriteScale->y = mSprites[currentSprite].height;

	}
	m_Dirty = false;
}

void Animator::LoadSprite(const char* a_pSpriteSheet)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	doc.LoadFile(a_pSpriteSheet); // load the document
	rootNode = doc.FirstChildElement("atlas");// set the root node
	currentNode = rootNode;

	//currentNode = rootNode->FirstChild(); // set the current node to the root nodes first child
	childElement = currentNode->ToElement();
	atlas.width = (float)childElement->IntAttribute("width");
	atlas.height = (float)childElement->IntAttribute("height");
	atlas.sSheet = childElement->Attribute("sheet");
	atlas.sAnimations = childElement->Attribute("animations");


	for (childElement = currentNode->FirstChildElement();
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		mSprites[str].Name = str;
		mSprites[str].x0 = childElement->IntAttribute("x0");
		mSprites[str].x1 = childElement->IntAttribute("x1");
		mSprites[str].y0 = childElement->IntAttribute("y0");
		mSprites[str].y1 = childElement->IntAttribute("y1");
		mSprites[str].height = mSprites[str].y1 - mSprites[str].y0;
		mSprites[str].width = mSprites[str].x1 - mSprites[str].x0;
	}
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
			mAnimations[aniName].push_back(str);
			i++;
		}
	}
std:printf("Animation load done!\n");
}
void Animator::SetAnimation(std::string animation, PlayType type)
{
	currentAnimation = animation;
	currentFrame = 0;
	loopFrame = 0;
	currentPlayType = type;
	switch (type){
	case ONCE:

		break;
	case LOOP:
		loopFrame = 0;
		break;
	case PINGPONG:
		break;
	case REVERSE:
		currentFrame = mAnimations[currentAnimation].size();
		loopFrame = currentFrame;
		break;
	case RANDOMLOOP:
	case RANDOM:
		/*srand(time(NULL));
		currentFrame =  (unsigned int)(rand() % mAnimations[currentAnimation].size());
		loopFrame = currentFrame;
		*/break;
	case LOOPSECTION:
		SetAnimation(animation, type, 0);
	case SINGLE:
		break;
	default:
		break;
	}
	currentSprite = mAnimations.at(currentAnimation)[currentFrame];
	SetSprite();


}

void Animator::SetAnimation(std::string animation, PlayType type, int frame)
{
	switch (type)
	{
	case LOOPSECTION:
		currentAnimation = animation;
		currentFrame = 0;
		currentPlayType = type;
		loopFrame = frame;
		break;
	default:
		SetAnimation(animation, type);
		break;
	}

}

void Animator::PlayAnimation()
{
	elapsedTime += getDeltaTime();

	if (elapsedTime > m_dFrames){
		elapsedTime = 0;
		m_Dirty = true;
		switch (currentPlayType){
		case ONCE:
			if (mAnimations.at(currentAnimation)[currentFrame] != mAnimations.at(currentAnimation).back())
			{
				currentFrame++;
				currentSprite = mAnimations.at(currentAnimation)[currentFrame];
			}
			break;
		case LOOPSECTION:
		case LOOP:
			if (mAnimations.at(currentAnimation)[currentFrame] == mAnimations.at(currentAnimation).back())
			{
				currentFrame = loopFrame;
				currentSprite = mAnimations.at(currentAnimation)[currentFrame];
			}
			else
			{
				currentFrame++;
				currentSprite = mAnimations.at(currentAnimation)[currentFrame];
			}
			break;
		case PINGPONG:
			break;
		case REVERSE:
			currentFrame = mAnimations[currentAnimation].size();
			loopFrame = currentFrame;
			break;
		case RANDOMLOOP:
		case RANDOM:
			/*	srand(time(NULL));
			currentFrame =  rand() % mAnimations[currentAnimation].size();
			loopFrame = currentFrame;
			*/break;
		case SINGLE:
			break;
		default:
			break;
		}
		SetSprite();
	}



}
