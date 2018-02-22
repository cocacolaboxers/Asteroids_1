#include "Asteroid.hpp"

const float SIZE_REDUCING_FACTOR = 0.5; // Reduces a point's coordinates
const float SIZE_ENLARGING_FACTOR = 1.5; // Enlarges a point's coodinates

Asteroid::Asteroid(Size size)
{
	m_asteroid_size = size;
	ArrangeEntityPoints();
}

void Asteroid::ArrangeEntityPoints()
{
	switch (m_asteroid_size)
	{
	case Asteroid::Size::SMALL:
		entityPoints.push_back(Vector2(0.0f, 100.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(20.0f, 90.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(40.0f, 80.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(60.0f, 40.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(70.0f, 20.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(60.0f, -20.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(40.0f, -15.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(20.0f, -20.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(0.0f, -50.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(-20.0f, -35.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(-50.0f, 2.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(-60.0f, 10.0f)*SIZE_REDUCING_FACTOR);
		entityPoints.push_back(Vector2(-40.0f, 80.0f)*SIZE_REDUCING_FACTOR);
		break;
	case Asteroid::Size::MEDIUM:
		entityPoints.push_back(Vector2(0.0f, 100.0f));
		entityPoints.push_back(Vector2(20.0f, 90.0f));
		entityPoints.push_back(Vector2(40.0f, 80.0f));
		entityPoints.push_back(Vector2(60.0f, 40.0f));
		entityPoints.push_back(Vector2(70.0f, 20.0f));
		entityPoints.push_back(Vector2(60.0f, -20.0f));
		entityPoints.push_back(Vector2(40.0f, -15.0f));
		entityPoints.push_back(Vector2(20.0f, -20.0f));
		entityPoints.push_back(Vector2(0.0f, -50.0f));
		entityPoints.push_back(Vector2(-20.0f, -35.0f));
		entityPoints.push_back(Vector2(-50.0f, 2.0f));
		entityPoints.push_back(Vector2(-60.0f, 10.0f));
		entityPoints.push_back(Vector2(-40.0f, 80.0f));
		break;
	case Asteroid::Size::BIG:
		entityPoints.push_back(Vector2(0.0f, 100.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(20.0f, 90.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(40.0f, 80.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(60.0f, 40.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(70.0f, 20.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(60.0f, -20.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(40.0f, -15.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(20.0f, -20.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(0.0f, -50.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(-20.0f, -35.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(-50.0f, 2.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(-60.0f, 10.0f)*SIZE_ENLARGING_FACTOR);
		entityPoints.push_back(Vector2(-40.0f, 80.0f)*SIZE_ENLARGING_FACTOR);
		break;
	default:
		break;
	}
}

void Asteroid::Update(float deltaTime)
{
}

Asteroid::Size Asteroid::GetSize()
{
	return m_asteroid_size;
}

void Asteroid::Render()
{
	glLoadIdentity();
	glTranslatef(entityPosition.x, entityPosition.y, 0.0f);
	glRotatef(entityOrientation, 0.0f, 0.0f, 1.0f);

	//Draw Asteroid
	DrawEntity();
}