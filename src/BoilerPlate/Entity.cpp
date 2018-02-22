#include "Entity.hpp"

const float INITIAL_WINDOW_WIDTH = 1136.0f;
const float INITIAL_WINDOW_HEIGHT = 640.0f;

Entity::Entity()
{
	entityPosition = Vector2(Vector2::Origin);
	entityOrientation = 0.0f;

	minWindowHeight = -INITIAL_WINDOW_HEIGHT / 2;
	maxWindowHeight = -minWindowHeight;
	minWindowWidth = -INITIAL_WINDOW_WIDTH / 2;
	maxWindowWidth = -minWindowWidth;
}

void Entity::DrawEntity()
{
	std::vector<Vector2>::iterator it = entityPoints.begin();

	glBegin(GL_LINE_LOOP);
	for (; it != entityPoints.end(); it++)
	{
		glVertex2f((*it).x, (*it).y);
	}

	glEnd();
}

void Entity::OnWindowResize(float newWindowHeight, float newWindowWidth)
{
	minWindowHeight = -newWindowHeight / 2;
	maxWindowHeight = -minWindowHeight;
	minWindowWidth = -newWindowWidth / 2;
	maxWindowWidth = -minWindowWidth;
}

void Entity::ArrangeEntityPoints(void)
{

}

void Entity::Update(float deltaTime)
{
	entityPosition.x += entityVelocity.x * static_cast<float> (deltaTime); // displacement = velocity * time
	entityPosition.y += entityVelocity.y * static_cast<float> (deltaTime);

	entityPosition.x = Warp(entityPosition.x, minWindowWidth, maxWindowWidth);
	entityPosition.y = Warp(entityPosition.y, minWindowHeight, maxWindowHeight);
}

void Entity::Render(void)
{

}

void Entity::MoveForward(void)
{

}

float Entity::Warp(float coordinate, float min, float max)
{
	if (coordinate < min) return max - (min - coordinate);
	if (coordinate > max) return min + (coordinate - max);
	return coordinate;
}