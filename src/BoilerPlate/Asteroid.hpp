#pragma once

#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Entity.hpp"

class Asteroid
{
public:
	/*ENUMERATED TYPE*/
	enum struct Size
	{
		SMALL,
		MEDIUM,
		BIG
	};
	/*CTOR*/
	Asteroid(Size);

	/*PUBLIC FUNCTIONS*/
	void Update(void);
	void Render(void);
	Size GetSize(void);
	void DrawAsteroid(void);
	void ArrangeAsteroidPoints(void);

private:
	/*PRIVATE MEMBERS*/
	Vector2 asteroidPosition;
	Size asteroidSize;
	float asteroidOrientation;
	std::vector<Vector2> asteroidPoints;
};

#endif // !_ASTEROID_H_
