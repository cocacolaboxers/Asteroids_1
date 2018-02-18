#include "Asteroid.hpp"

Asteroid::Asteroid(Size size)
{
	asteroidSize = size;
	ArrangeEntityPoints();
}

void Asteroid::ArrangeEntityPoints()
{
	switch (asteroidSize)
	{
	case Asteroid::Size::SMALL:
		entityPoints.push_back(Vector2(0.0f, 100.0f)*0.5);
		entityPoints.push_back(Vector2(20.0f, 90.0f)*0.5);
		entityPoints.push_back(Vector2(40.0f, 80.0f)*0.5);
		entityPoints.push_back(Vector2(60.0f, 40.0f)*0.5);
		entityPoints.push_back(Vector2(70.0f, 20.0f)*0.5);
		entityPoints.push_back(Vector2(60.0f, -20.0f)*0.5);
		entityPoints.push_back(Vector2(40.0f, -15.0f)*0.5);
		entityPoints.push_back(Vector2(20.0f, -20.0f)*0.5);
		entityPoints.push_back(Vector2(0.0f, -50.0f)*0.5);
		entityPoints.push_back(Vector2(-20.0f, -35.0f)*0.5);
		entityPoints.push_back(Vector2(-50.0f, 2.0f)*0.5);
		entityPoints.push_back(Vector2(-60.0f, 10.0f)*0.5);
		entityPoints.push_back(Vector2(-40.0f, 80.0f)*0.5);
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
		entityPoints.push_back(Vector2(0.0f, 100.0f)*1.5);
		entityPoints.push_back(Vector2(20.0f, 90.0f)*1.5);
		entityPoints.push_back(Vector2(40.0f, 80.0f)*1.5);
		entityPoints.push_back(Vector2(60.0f, 40.0f)*1.5);
		entityPoints.push_back(Vector2(70.0f, 20.0f)*1.5);
		entityPoints.push_back(Vector2(60.0f, -20.0f)*1.5);
		entityPoints.push_back(Vector2(40.0f, -15.0f)*1.5);
		entityPoints.push_back(Vector2(20.0f, -20.0f)*1.5);
		entityPoints.push_back(Vector2(0.0f, -50.0f)*1.5);
		entityPoints.push_back(Vector2(-20.0f, -35.0f)*1.5);
		entityPoints.push_back(Vector2(-50.0f, 2.0f)*1.5);
		entityPoints.push_back(Vector2(-60.0f, 10.0f)*1.5);
		entityPoints.push_back(Vector2(-40.0f, 80.0f)*1.5);
		break;
	default:
		break;
	}
}

void Asteroid::Update(void)
{
}

Asteroid::Size Asteroid::GetSize()
{
	return asteroidSize;
}

void Asteroid::Render()
{
	glLoadIdentity();
	glTranslatef(entityPosition->x, entityPosition->y, 0.0f);
	glRotatef(entityOrientation, 0.0f, 0.0f, 1.0f);

	//Draw Asteroid
	DrawEntity();
}