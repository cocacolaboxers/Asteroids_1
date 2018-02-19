#include "ColorPalette.hpp"

ColorPalette::ColorPalette()
{
	RED = Color(1.0f, 0.0f, 0.0f, 0.0f);
	YELLOW = Color(1.0f, 1.0f, 0.0f, 0.0f);
	CYAN = Color(0.0f, 1.0f, 1.0f, 0.0f);
	GRAY = Color(0.5f, 0.5f, 0.5f, 0.5f);
	ORANGE = Color(1.0f, 0.5f, 0.0f, 0.0f);
	NAVY = Color(0.1f, 0.1f, 0.15f, 1.0f);
}


ColorPalette::~ColorPalette()
{
}
