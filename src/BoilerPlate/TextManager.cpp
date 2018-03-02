#include "TextManager.hpp"

TextManager::TextManager()
{
}

TextManager::TextManager(TTF_Font* selectedFont)
{
	m_font = selectedFont;
}

bool TextManager::InitializeLibrary()
{
	if (TTF_Init() == -1) {
		SDL_Log("TTF_Init: %s\n", TTF_GetError());
		return false;
	}
	else
		return true;
}

void TextManager::CleanUpLibrary()
{
	TTF_Quit();
}

unsigned int TextManager::power_two_floor(unsigned int value)
{
	unsigned int power = 2, nextValue = power * 2;
	while ((nextValue *= 2) <= value)
		power *= 2;
	return power * 2;
}

void TextManager::RenderText(std::string message, SDL_Color color, float x, float y, int size)
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);

	SDL_Surface *surface;

	//Render font to a SDL_Surface
	if ((surface = TTF_RenderText_Blended(m_font, message.c_str(), color)) == nullptr) {
		m_font = NULL;
		TTF_CloseFont(m_font);
		//std::cout << "TTF_RenderText error: " << std::endl;
		return;
	}

	GLuint texId;

	//Generate OpenGL texture
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	//Avoid mipmap filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Find the first power of two for OpenGL image 
	int w = power_two_floor(surface->w) * 2;
	int h = power_two_floor(surface->h) * 2;

	//Create a surface to the correct size in RGB format, and copy the old image
	SDL_Surface * s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(surface, NULL, s, NULL);

	//Copy the created image into OpenGL format
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);

	//Draw the OpenGL texture as a Quad
	glBegin(GL_QUADS); {
		glTexCoord2d(0, 1); glVertex3f(0, 0, 0);
		glTexCoord2d(1, 1); glVertex3f(0 + static_cast<float>(surface->w), 0, 0);
		glTexCoord2d(1, 0); glVertex3f(0 + static_cast<float>(surface->w), 0 + static_cast<float>(surface->h), 0);
		glTexCoord2d(0, 0); glVertex3f(0, 0 + static_cast<float>(surface->h), 0);
	} glEnd();
	glDisable(GL_TEXTURE_2D);

	//Cleanup
	SDL_FreeSurface(s);
	SDL_FreeSurface(surface);
	glDeleteTextures(1, &texId);
}





