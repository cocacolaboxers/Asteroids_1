#pragma once
#ifndef _TEXT_MANAGER_H_
#define _TEXT_MANAGER_H_
#include "OpenGLincludes.hpp"
#include <string>

class TextManager {
public:
	/*CTOR*/
	TextManager();
	TextManager(TTF_Font*);

	/*PUBLIC FUNCTIONS*/
	bool InitializeLibrary();
	void CleanUpLibrary();
	unsigned int power_two_floor(unsigned int);
	void RenderText(std::string, SDL_Color, float, float, int);
private:
	/*PRIVATE MEMBERS*/
	TTF_Font* m_font;

};

#endif // !_TEXT_MANAGER_H_

