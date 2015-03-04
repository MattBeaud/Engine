#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SOIL.h>


#include <vector>
#include <string>
#include <fstream>
#include <GLFW/glfw3.h>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ctime>
#include <iostream>
#include <tinyxml2.h>

#include "Shape.h"
#include "Utilities.h"


struct AniSprite
{
	std::string Name;
	float width, height;
	float x0, x1, y0, y1;
};
//AniSprite testSprite;

struct Atlas
{
	float width, height;
	std::string sSheet;
	std::string sAnimations;
};
typedef std::vector<std::string> frame;

class Animator
{
public:
	Animator(void);
	~Animator(void);

	void Update();
	void Initialize(Shape * shape, glm::vec2 &Scale);
	void ImportSheet(const char* a_pSpriteSheet);
	void SetAnimation(std::string animation, PlayType type);
	void SetAnimation(std::string animation, PlayType type, int frame);
	void PlayAnimation();
	void SetSprite();
	void LoadSprite(const char* a_pSpriteSheet);
	void LoadAnimations(const char* a_pAnimationSheet);
	void SetUVData(float2 * data);
	std::map<std::string, AniSprite> mSprites;
	std::map<std::string, frame> mAnimations;
	Atlas atlas;
	
	//float2 * m_UVData;
	float * U;
	float * V;
	float * UWidth;
	float * VHeight;

	glm::vec2 * m_SpriteScale;
	std::string currentAnimation, currentSprite;

	int currentFrame, loopFrame;
	double m_dFrames;
	PlayType currentPlayType;


	double elapsedTime = 0;
	bool m_Dirty = false;

};

