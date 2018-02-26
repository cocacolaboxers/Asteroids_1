#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.hpp"
#include "Asteroid.hpp"

class Player : public Entity
{
public:
	/*CTOR*/
	Player();

	/*PUBLIC FUNCTIONS*/
	void Update(float) override;
	void Render(void) override;

	void MoveForward(void);
	void RotateLeft(void);
	void RotateRight(void);
	void DrawThrust(void);
	void SetThrustingStatus(bool);
	void ArrangeEntityPoints(void) override;
	void ArrangeThrusterPoints(void);


private:
	/*MEMBERS*/
	bool m_isThrusting;
	std::vector<Vector2> m_thrusterPoints;
	float m_playerCurrentSpeed;
};

#endif // !_PLAYER_H_
