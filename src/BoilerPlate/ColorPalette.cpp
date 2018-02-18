#include "ColorPalette.hpp"

ColorPalette::ColorPalette()
{
	red = Color(1.0f, 0.0f, 0.0f, 0.0f);
	yellow = Color(1.0f, 1.0f, 0.0f, 0.0f);
	cyan = Color(0.0f, 1.0f, 1.0f, 0.0f);
	gray = Color(0.5f, 0.5f, 0.5f, 0.5f);
	orange = Color(1.0f, 0.5f, 0.0f, 0.0f);
	navy = Color(0.1f, 0.1f, 0.15f, 1.0f);
}


ColorPalette::~ColorPalette()
{
}
