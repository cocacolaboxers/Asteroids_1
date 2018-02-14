#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Vector2.hpp"
#include "SDLEvent.hpp"
#include "MathUtilities.hpp"

class Player
{
public:
	/*CTOR*/
	Player();

	/*PUBLIC FUNCTIONS*/
	void Update(void);
	void Render(void);

	float Warp(float, float, float);
	void MoveForward(void);
	void RotateLeft(void);
	void RotateRight(void);
	void DrawShip(void);
	void DrawThrust(void);
	void OnWindowResize(float, float);
	void setThrustingStatus(bool);

private:
	/*MEMBERS*/
	Vector2* playerPosition;
	float playerOrientation;
	float mass;

	bool isThrusting;
	float minWindowHeight;
	float maxWindowHeight;
	float minWindowWidth;
	float maxWindowWidth;
};

#endif // !_PLAYER_H_
