#include "Asteroid.hpp"

Asteroid::Asteroid(Size size)
{
	asteroidSize = size;
	asteroidOrientation = 0.0f;

	ArrangeAsteroidPoints();
}

void Asteroid::DrawAsteroid()
{
	glBegin(GL_LINE_LOOP);
	for (std::vector<Vector2>::iterator it = asteroidPoints.begin();
		it != asteroidPoints.end(); it++)
	{
		glVertex2f((*it).x, (*it).y);
	}

	glEnd();
}

void Asteroid::ArrangeAsteroidPoints()
{
	switch (asteroidSize)
	{
	case Asteroid::Size::SMALL:
		asteroidPoints.push_back(Vector2(0.0f, 100.0f)*0.5);
		asteroidPoints.push_back(Vector2(20.0f, 90.0f)*0.5);
		asteroidPoints.push_back(Vector2(40.0f, 80.0f)*0.5);
		asteroidPoints.push_back(Vector2(60.0f, 40.0f)*0.5);
		asteroidPoints.push_back(Vector2(70.0f, 20.0f)*0.5);
		asteroidPoints.push_back(Vector2(60.0f, -20.0f)*0.5);
		asteroidPoints.push_back(Vector2(40.0f, -15.0f)*0.5);
		asteroidPoints.push_back(Vector2(20.0f, -20.0f)*0.5);
		asteroidPoints.push_back(Vector2(0.0f, -50.0f)*0.5);
		asteroidPoints.push_back(Vector2(-20.0f, -35.0f)*0.5);
		asteroidPoints.push_back(Vector2(-50.0f, 2.0f)*0.5);
		asteroidPoints.push_back(Vector2(-60.0f, 10.0f)*0.5);
		asteroidPoints.push_back(Vector2(-40.0f, 80.0f)*0.5);
		break;
	case Asteroid::Size::MEDIUM:
		asteroidPoints.push_back(Vector2(0.0f, 100.0f));
		asteroidPoints.push_back(Vector2(20.0f, 90.0f));
		asteroidPoints.push_back(Vector2(40.0f, 80.0f));
		asteroidPoints.push_back(Vector2(60.0f, 40.0f));
		asteroidPoints.push_back(Vector2(70.0f, 20.0f));
		asteroidPoints.push_back(Vector2(60.0f, -20.0f));
		asteroidPoints.push_back(Vector2(40.0f, -15.0f));
		asteroidPoints.push_back(Vector2(20.0f, -20.0f));
		asteroidPoints.push_back(Vector2(0.0f, -50.0f));
		asteroidPoints.push_back(Vector2(-20.0f, -35.0f));
		asteroidPoints.push_back(Vector2(-50.0f, 2.0f));
		asteroidPoints.push_back(Vector2(-60.0f, 10.0f));
		asteroidPoints.push_back(Vector2(-40.0f, 80.0f));
		break;
	case Asteroid::Size::BIG:
		asteroidPoints.push_back(Vector2(0.0f, 100.0f)*1.5);
		asteroidPoints.push_back(Vector2(20.0f, 90.0f)*1.5);
		asteroidPoints.push_back(Vector2(40.0f, 80.0f)*1.5);
		asteroidPoints.push_back(Vector2(60.0f, 40.0f)*1.5);
		asteroidPoints.push_back(Vector2(70.0f, 20.0f)*1.5);
		asteroidPoints.push_back(Vector2(60.0f, -20.0f)*1.5);
		asteroidPoints.push_back(Vector2(40.0f, -15.0f)*1.5);
		asteroidPoints.push_back(Vector2(20.0f, -20.0f)*1.5);
		asteroidPoints.push_back(Vector2(0.0f, -50.0f)*1.5);
		asteroidPoints.push_back(Vector2(-20.0f, -35.0f)*1.5);
		asteroidPoints.push_back(Vector2(-50.0f, 2.0f)*1.5);
		asteroidPoints.push_back(Vector2(-60.0f, 10.0f)*1.5);
		asteroidPoints.push_back(Vector2(-40.0f, 80.0f)*1.5);
		break;
	default:
		break;
	}
}

Asteroid::Size Asteroid::GetSize()
{
	return asteroidSize;
}

void Asteroid::Render()
{
	glLoadIdentity();
	glTranslatef(asteroidPosition.x, asteroidPosition.y, 0.0f);
	glRotatef(asteroidOrientation, 0.0f, 0.0f, 1.0f);

	//Draw Asteroid
	DrawAsteroid();
}

void Asteroid::Update()
{

}