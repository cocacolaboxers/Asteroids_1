#pragma once

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

class Color
{
public:
	GLfloat redValue, greenValue, blueValue, alphaValue;

	Color();
	Color(GLfloat newRedValue, GLfloat newGreenValue, GLfloat newBlueValue, GLfloat newAlphaValue);
	~Color();
};

