#pragma once

#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Entity.hpp"

class Asteroid : public Entity
{
public:
	/*ENUMERATED TYPE*/
	enum struct Size
	{
		SMALL = 0,
		MEDIUM = 1,
		BIG = 2
	};
	/*CTOR*/
	Asteroid(Size, float, float, float);

	/*PUBLIC FUNCTIONS*/
	void Render(void) override;
	void ArrangeEntityPoints(void) override;
	void Update(float) override;
	void ApplyImpulse(Vector2) override;

	Size GetSize(void);

private:
	/*PRIVATE MEMBERS*/
	Size m_asteroid_size;
};

#endif // !_ASTEROID_H_
