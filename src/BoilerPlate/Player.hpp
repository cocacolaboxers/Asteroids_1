#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.hpp"

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
	void SetThrustingStatus(bool);
	void ArrangeShipPoints(void);
	void ArrangeThrusterPoints(void);

private:
	/*MEMBERS*/
	Vector2* playerPosition;
	float playerOrientation;
	float playerMass;

	bool isThrusting;
	float minWindowHeight;
	float maxWindowHeight;
	float minWindowWidth;
	float maxWindowWidth;

	std::vector<Vector2> shipPoints;
	std::vector<Vector2> thrusterPoints;
};

#endif // !_PLAYER_H_
