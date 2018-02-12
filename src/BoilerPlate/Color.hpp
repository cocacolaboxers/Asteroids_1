#pragma once

class Color
{
public:
	float redValue, greenValue, blueValue, alphaValue;

	Color();
	Color(float newRedValue, float newGreenValue, float newBlueValue, float newAlphaValue);
	~Color();
};