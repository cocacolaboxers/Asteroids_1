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
		SMALL,
		MEDIUM,
		BIG
	};
	/*CTOR*/
	Asteroid(Size);

	/*PUBLIC FUNCTIONS*/
	void Render(void) override;
	void ArrangeEntityPoints(void) override;
	void Update(float) override;

	Size GetSize(void);

private:
	/*PRIVATE MEMBERS*/
	Size m_asteroid_size;
};

#endif // !_ASTEROID_H_
