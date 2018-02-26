#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.hpp"

class Bullet : public Entity
{
public:
	/*CTOR*/
	Bullet();
	void ApplyImpulse(Vector2) override;
	void Update(float) override;
	void Render(void) override;
	bool GetStatus(void);

private:
	float m_traveledDistance;
	bool	  m_hasDisappeared;
};

#endif // !_BULLET_H_

