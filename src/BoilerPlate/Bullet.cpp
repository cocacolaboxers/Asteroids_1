#include "Bullet.hpp"

const float MAX_TRAVELED_DISTANCE = 100.0f;

Bullet::Bullet()
{
	m_traveledDistance = 0.0;
	m_entityRadius = 4.0f;
	m_hasDisappeared = false;
}

void Bullet::ApplyImpulse(Vector2 impulse)
{
	if (m_entityMass > 0)
	{
		m_entityVelocity.x -= (impulse.x / m_entityMass);
		m_entityVelocity.y += (impulse.y / m_entityMass);
	}
}

void Bullet::Update(float deltaTime)
{
	//Bullet has to disappear at some point
	if (m_traveledDistance < MAX_TRAVELED_DISTANCE)
		m_traveledDistance++;
	else
		m_hasDisappeared = true;

	Entity::Update(deltaTime);
}

void Bullet::Render(void)
{
	if (!m_hasDisappeared)
	{
		glLoadIdentity();
		glPointSize(3.0f);
		glBegin(GL_POINTS);
		glVertex2f(m_entityPosition.x, m_entityPosition.y);
		glEnd();

		//Draw Bounding Circles
		DrawBoundingCircle();
	}
}

bool Bullet::GetStatus(void)
{
	return m_hasDisappeared;
}
