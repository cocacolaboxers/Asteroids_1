#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Vector2.hpp"
#include "SDLEvent.hpp"


class Player
{
public:
	/*CTOR*/
	Player();

	/*PUBLIC FUNCTIONS*/
	void Update(void);
	void Render(void);

	void Move(const Vector2& unit);
	void Warp(void);
	void MoveForward(void);
	void RotateLeft(void);
	void RotateRight(void);

	/*PUBLIC MEMBERS*/
	bool thrusterActivated;

private:
	/*MEMBERS*/
	Vector2* playerPosition;
};

#endif // !_PLAYER_H_
