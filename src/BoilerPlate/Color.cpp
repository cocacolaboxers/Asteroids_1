#include "Color.h"

Color::Color()
{
}

Color::Color(GLfloat newRedValue, GLfloat newGreenValue, GLfloat newBlueValue, GLfloat newAlphaValue)
{
	redValue = newRedValue;
	greenValue = newGreenValue;
	blueValue = newBlueValue;
	alphaValue = newAlphaValue;
}

Color::~Color()
{

}