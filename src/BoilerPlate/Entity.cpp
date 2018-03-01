#include "Entity.hpp"

const float INITIAL_WINDOW_WIDTH = 1136.0f;
const float INITIAL_WINDOW_HEIGHT = 640.0f;

Entity::Entity()
{
	m_entityPosition = Vector2(Vector2::Origin);
	m_entityOrientation = 0.0f;
	m_entityMass = 1.0f;
	m_isDebugging = false;
	m_hasCollided = false;

	m_minWindowHeight = -INITIAL_WINDOW_HEIGHT / 2;
	m_maxWindowHeight = -m_minWindowHeight;
	m_minWindowWidth = -INITIAL_WINDOW_WIDTH / 2;
	m_maxWindowWidth = -m_minWindowWidth;
}

void Entity::DrawEntity()
{
	std::vector<Vector2>::iterator it = m_entityPoints.begin();

	glBegin(GL_LINE_LOOP);
	for (; it != m_entityPoints.end(); it++)
	{
		glVertex2f((*it).x, (*it).y);
	}

	glEnd();
}

void Entity::OnWindowResize(float newWindowHeight, float newWindowWidth)
{
	m_minWindowHeight = -newWindowHeight / 2;
	m_maxWindowHeight = -m_minWindowHeight;
	m_minWindowWidth = -newWindowWidth / 2;
	m_maxWindowWidth = -m_minWindowWidth;
}

void Entity::ArrangeEntityPoints(void)
{

}

void Entity::Update(float deltaTime)
{
	m_entityPosition.x += m_entityVelocity.x * static_cast<float> (deltaTime); // displacement = velocity * time
	m_entityPosition.y += m_entityVelocity.y * static_cast<float> (deltaTime);

	m_entityPosition.x = Warp(m_entityPosition.x, m_minWindowWidth, m_maxWindowWidth);
	m_entityPosition.y = Warp(m_entityPosition.y, m_minWindowHeight, m_maxWindowHeight);
}

void Entity::Render(void)
{

}

float Entity::Warp(float coordinate, float min, float max)
{
	if (coordinate < min) return max - (min - coordinate);
	if (coordinate > max) return min + (coordinate - max);
	return coordinate;
}

void Entity::ApplyImpulse(Vector2 impulse)
{
	if (m_entityMass > 0)
	{
		m_entityVelocity.x -= (impulse.x / m_entityMass) * sinf(m_utility.ToRadians(m_entityOrientation));
		m_entityVelocity.y += (impulse.y / m_entityMass) * cosf(m_utility.ToRadians(m_entityOrientation));
	}
}

void Entity::DrawBoundingCircle(void)
{
	if (m_isDebugging)
	{
		int lineAmount = 100;
		float twicePI = 2.0f * m_utility.PI;

		glLoadIdentity(); //Reload matrix to ensure translation won't be applied again on the already translated matrix

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= lineAmount; i++)
		{
			glVertex2f(m_entityPosition.x + (m_entityRadius * cos(i *  twicePI / lineAmount)),
				m_entityPosition.y + (m_entityRadius* sin(i * twicePI / lineAmount))
			);
		}
		glEnd();
	}
}

float Entity::CalculateDistanceBetweenEntities(Entity rhs)
{
	float distance;
	float deltaX = rhs.m_entityPosition.x - m_entityPosition.x;
	float deltaY = rhs.m_entityPosition.y - m_entityPosition.y;

	distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

	return distance;
}

Vector2 Entity::GetPosition(void)
{
	return m_entityPosition;
}

float Entity::GetRadius(void)
{
	return m_entityRadius;
}

bool Entity::DetectCollision(Entity rhs)
{
	float radialDistance = m_entityRadius + rhs.m_entityRadius;

	float distanceBetweenEntities = CalculateDistanceBetweenEntities(rhs);

	bool detectedCollision = distanceBetweenEntities <= radialDistance;

	if (detectedCollision && !m_isDebugging) 
	{
			m_hasCollided = true;
	}

	return detectedCollision;
}

void Entity::ToggleDebuggingFeatures(bool status)
{
	m_isDebugging = status;
}

bool Entity::GetDebuggingStatus()
{
	return m_isDebugging;
}

bool Entity::GetCollisionStatus()
{
	return m_hasCollided;
}

void Entity::ForcePositionChange(float newXcoordinate, float newYcoordinate)
{
	m_entityPosition.x = newXcoordinate;
	m_entityPosition.y = newYcoordinate;
}

float Entity::GetOrientation(void)
{
	return m_entityOrientation;
}

std::vector<Vector2> Entity::GetEntityPoints(void)
{
	return m_entityPoints;
}

void Entity::setActivity(bool status)
{
	m_isInactive = status;
}




