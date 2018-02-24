#include "Asteroid.hpp"

const float SIZE_REDUCING_FACTOR = 0.8; // Reduces a point's coordinates
const float SIZE_ENLARGING_FACTOR = 1.5; // Enlarges a point's coodinates
const float ROTATION_SPEED = 90.0f;
const float MOVING_SPEED = 60.0f;


Asteroid::Asteroid(Size size, float xCoordinate, float yCoordinate, float initialOrientation)
{
	m_asteroidSize = size;
	m_entityOrientation = initialOrientation;
	ArrangeEntityPoints();
	m_entityPosition = Vector2(xCoordinate, yCoordinate);
	ApplyImpulse(Vector2(MOVING_SPEED, MOVING_SPEED));
}

void Asteroid::ArrangeEntityPoints()
{
	switch (m_asteroidSize)
	{
	case Asteroid::Size::SMALL:
		m_entityPoints.push_back(Vector2(0.0f, 50.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(10.0f, 45.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(20.0f, 40.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(30.0f, 20.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(35.0f, 10.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(30.0f, -10.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(20.0f, -7.5f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(10.0f, -10.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(0.0f, -25.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(-10.0f, -17.5f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(-25.0f, 1.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(-30.0f, 5.0f)*SIZE_REDUCING_FACTOR);
		m_entityPoints.push_back(Vector2(-20.0f, 40.0f)*SIZE_REDUCING_FACTOR);
		break;
	case Asteroid::Size::MEDIUM:
		m_entityPoints.push_back(Vector2(0.0f, 50.0f));
		m_entityPoints.push_back(Vector2(10.0f, 45.0f));
		m_entityPoints.push_back(Vector2(20.0f, 40.0f));
		m_entityPoints.push_back(Vector2(30.0f, 20.0f));
		m_entityPoints.push_back(Vector2(35.0f, 10.0f));
		m_entityPoints.push_back(Vector2(30.0f, -10.0f));
		m_entityPoints.push_back(Vector2(20.0f, -7.5f));
		m_entityPoints.push_back(Vector2(10.0f, -10.0f));
		m_entityPoints.push_back(Vector2(0.0f, -25.0f));
		m_entityPoints.push_back(Vector2(-10.0f, -17.5f));
		m_entityPoints.push_back(Vector2(-25.0f, 1.0f));
		m_entityPoints.push_back(Vector2(-30.0f, 5.0f));
		m_entityPoints.push_back(Vector2(-20.0f, 40.0f));
		break;
	case Asteroid::Size::BIG:
		m_entityPoints.push_back(Vector2(0.0f, 50.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(10.0f, 45.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(20.0f, 40.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(30.0f, 20.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(35.0f, 10.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(30.0f, -10.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(20.0f, -7.5f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(10.0f, -10.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(0.0f, -25.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(-10.0f, -17.5f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(-25.0f, 1.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(-30.0f, 5.0f)*SIZE_ENLARGING_FACTOR);
		m_entityPoints.push_back(Vector2(-20.0f, 40.0f)*SIZE_ENLARGING_FACTOR);
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
	int sizeBasedImpulse = ((int)m_asteroidSize + 1) * MOVING_SPEED; //Used to make asteroids move faster or slower acording to their size

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
	glLoadIdentity();
	glTranslatef(m_entityPosition.x, m_entityPosition.y, 0.0f);
	glRotatef(m_entityOrientation, 0.0f, 0.0f, 1.0f);

	//Draw Asteroid
	DrawEntity();

	//Draw Bounding Circles

}