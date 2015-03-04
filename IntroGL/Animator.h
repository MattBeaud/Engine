#pragma once
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SOIL.h>


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

	void ImportSheet(const char* a_pSpriteSheet);
    //void SetAnimation(std::string animation, PlayType type);
	void PlayAnimation();
	void LoadSprite(const char* a_pSpriteSheet);
	void LoadAnimations(const char* a_pAnimationSheet);
	//std::map<std::string, frame> mAnimations;
	Atlas atlas;

};

