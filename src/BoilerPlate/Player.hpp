#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Vector2.hpp"
#include "SDLEvent.hpp"


class Player
{
public:
	/*CTOR*/
	void Update(SDL_KeyboardEvent);
	void Render();
	Player();
	void thruster();
	bool thrusterActivated = false;

private:
	/*MEMBERS*/
	Vector2 position;
};

#endif // !_PLAYER_H_
