#include "Asteroid.hpp"

const float SIZE_ENLARGING_FACTOR_MEDIUM = 1.5; // Enlarges a point's coodinates
const float SIZE_ENLARGING_FACTOR_BIG = 2.0; // Enlarges a point's coodinates
const float ROTATION_SPEED = 90.0f;
const float MOVING_SPEED = 60.0f;


Asteroid::Asteroid(Size size, float xCoordinate, float yCoordinate, float initialOrientation)
{
	m_asteroidSize = size;
	m_entityOrientation = initialOrientation;
	ArrangeEntityPoints();
	m_entityPosition = Vector2(xCoordinate, yCoordinate);
	ApplyImpulse(Vector2(MOVING_SPEED, MOVING_SPEED));

	switch (m_asteroidSize)
	{
	case Asteroid::Size::SMALL:
		m_entityRadius = 24;
		break;

	case Asteroid::Size::MEDIUM:
		m_entityRadius = 24 * SIZE_ENLARGING_FACTOR_MEDIUM;
		break;

	case Asteroid::Size::BIG:
		m_entityRadius = 24 * SIZE_ENLARGING_FACTOR_BIG;
		break;
	}
}

void Asteroid::ArrangeEntityPoints()
{
	switch (m_asteroidSize)
	{
	case Asteroid::Size::SMALL:
		m_entityPoints.push_back(Vector2(0.0f, 22.0f));
		m_entityPoints.push_back(Vector2(4.0f, 21.0f));
		m_entityPoints.push_back(Vector2(8.0f, 21.5f));
		m_entityPoints.push_back(Vector2(13.0f, 19.0f));
		m_entityPoints.push_back(Vector2(16.0f, 17.0f));
		m_entityPoints.push_back(Vector2(18.0f, 10.0f));
		m_entityPoints.push_back(Vector2(20.0f, 7.0f));
		m_entityPoints.push_back(Vector2(23.0f, 3.0f));
		m_entityPoints.push_back(Vector2(24.0f, 0.0f));
		m_entityPoints.push_back(Vector2(20.0f, -7.f));
		m_entityPoints.push_back(Vector2(22.0f, -12.0f));
		m_entityPoints.push_back(Vector2(15.0f, -18.0f));
		m_entityPoints.push_back(Vector2(10.0f, -20.0f));
		m_entityPoints.push_back(Vector2(5.0f, -23.0f));
		m_entityPoints.push_back(Vector2(0.0f, -22.0f));
		m_entityPoints.push_back(Vector2(-5.0f, -21.5f));
		m_entityPoints.push_back(Vector2(-10.0f, -20.0f));
		m_entityPoints.push_back(Vector2(-15.0f, -16.0f));
		m_entityPoints.push_back(Vector2(-20.0f, -10.0f));
		m_entityPoints.push_back(Vector2(-22.0f, -6.0f));
		m_entityPoints.push_back(Vector2(-24.0f, 0.0f));
		m_entityPoints.push_back(Vector2(-25.0f, 5.0f));
		m_entityPoints.push_back(Vector2(-23.0f, 9.f));
		m_entityPoints.push_back(Vector2(-19.0f, 10.0f));
		m_entityPoints.push_back(Vector2(-16.0f, 13.0f));
		m_entityPoints.push_back(Vector2(-14.0f, 18.f));
		m_entityPoints.push_back(Vector2(-10.0f, 21.0f));
		m_entityPoints.push_back(Vector2(-5.0f, 23.0f));
		break;
	case Asteroid::Size::MEDIUM:
		m_entityPoints.push_back(Vector2(0.0f, 22.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(4.0f, 21.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(8.0f, 21.5f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(13.0f, 19.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(16.0f, 17.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(18.0f, 10.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(20.0f, 7.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(23.0f, 3.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(24.0f, 0.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(20.0f, -7.f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(22.0f, -12.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(15.0f, -18.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(10.0f, -20.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(5.0f, -23.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(0.0f, -22.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-5.0f, -21.5f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-10.0f, -20.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-15.0f, -16.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-20.0f, -10.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-22.0f, -6.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-24.0f, 0.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-25.0f, 5.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-23.0f, 9.f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-19.0f, 10.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-16.0f, 13.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-14.0f, 18.f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-10.0f, 21.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		m_entityPoints.push_back(Vector2(-5.0f, 23.0f) * SIZE_ENLARGING_FACTOR_MEDIUM);
		break;
	case Asteroid::Size::BIG:
		m_entityPoints.push_back(Vector2(0.0f, 22.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(4.0f, 21.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(8.0f, 21.5f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(13.0f, 19.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(16.0f, 17.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(18.0f, 10.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(20.0f, 7.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(23.0f, 3.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(24.0f, 0.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(20.0f, -7.f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(22.0f, -12.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(15.0f, -18.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(10.0f, -20.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(5.0f, -23.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(0.0f, -22.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-5.0f, -21.5f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-10.0f, -20.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-15.0f, -16.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-20.0f, -10.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-22.0f, -6.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-24.0f, 0.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-25.0f, 5.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-23.0f, 9.f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-19.0f, 10.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-16.0f, 13.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-14.0f, 18.f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-10.0f, 21.0f) * SIZE_ENLARGING_FACTOR_BIG);
		m_entityPoints.push_back(Vector2(-5.0f, 23.0f) * SIZE_ENLARGING_FACTOR_BIG);
		break;
	default:
		break;
	}
}

void Asteroid::Update(float deltaTime)
{
	//Rotate the asteroid
	m_entityOrientation += ROTATION_SPEED * deltaTime;
	Entity::Update(deltaTime);
}

void Asteroid::ApplyImpulse(Vector2 impulse)
{
	float sizeBasedImpulse = ((int)m_asteroidSize + 1) * MOVING_SPEED; //Used to make asteroids move faster or slower acording to their size

	if (m_entityMass > 0)
	{
		m_entityVelocity.x -= (impulse.x / m_entityMass) * sinf(m_utility.ToRadians(m_entityOrientation)) + sizeBasedImpulse;
		m_entityVelocity.y += (impulse.y / m_entityMass) * cosf(m_utility.ToRadians(m_entityOrientation)) + sizeBasedImpulse;
	}
}

Asteroid::Size Asteroid::GetSize()
{
	return m_asteroidSize;
}

void Asteroid::Render()
{
	if (!m_hasCollided)
	{
		glLoadIdentity();
		glTranslatef(m_entityPosition.x, m_entityPosition.y, 0.0f);
		glRotatef(m_entityOrientation, 0.0f, 0.0f, 1.0f);

		//Draw Asteroid
		DrawEntity();

		//Draw Bounding Circles
		DrawBoundingCircle();
	}
}