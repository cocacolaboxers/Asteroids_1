#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.hpp"

class Player : public Entity
{
public:
	/*CTOR*/
	Player();

	/*PUBLIC FUNCTIONS*/
	void Update(void) override;
	void Render(void) override;

	void MoveForward(void) override;
	void RotateLeft(void);
	void RotateRight(void);
	void DrawThrust(void);
	void SetThrustingStatus(bool);
	void ArrangeEntityPoints(void) override;
	void ArrangeThrusterPoints(void);

private:
	/*MEMBERS*/
	bool isThrusting;
	std::vector<Vector2> thrusterPoints;
};

#endif // !_PLAYER_H_
