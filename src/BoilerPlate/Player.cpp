#include "Player.hpp"

const float INITIAL_WINDOW_WIDTH = 1136.0f;
const float INITIAL_WINDOW_HEIGHT = 640.0f ;
const float MOVING_SPEED = 10.0f;
const float ROTATION_SPEED = 10.0f; 
const float DESIRED_MAX_SPEED = 200;

Player::Player()
{
	m_isThrusting = false;
	ArrangeEntityPoints();
	ArrangeThrusterPoints();
}

void Player::ArrangeEntityPoints()
{
	entityPoints.push_back(Vector2(0.0f, 20.0f));
	entityPoints.push_back(Vector2(12.0f, -10.0f));
	entityPoints.push_back(Vector2(6.0f, -4.0f));
	entityPoints.push_back(Vector2(-6.0f, -4.0f));
	entityPoints.push_back(Vector2(-12.0f, -10.0f));
}

void Player::ArrangeThrusterPoints()
{
	m_thrusterPoints.push_back(Vector2(6.0f, -4.0f));
	m_thrusterPoints.push_back(Vector2(-6.0f, -4.0f));
	m_thrusterPoints.push_back(Vector2(0.0f, -14.0f));
}

void Player::Update(float deltaTime)
{
	m_playerCurrentSpeed = std::fabs(entityVelocity.Length());
	if(m_playerCurrentSpeed > DESIRED_MAX_SPEED)
	{
		entityVelocity.x = (entityVelocity.x / m_playerCurrentSpeed) * DESIRED_MAX_SPEED;
		entityVelocity.y = (entityVelocity.y / m_playerCurrentSpeed) * DESIRED_MAX_SPEED;
	}

	Entity::Update(deltaTime);
}

void Player::MoveForward()
{
	ApplyImpulse(Vector2(MOVING_SPEED, MOVING_SPEED));
}
 
void Player::RotateLeft()
{
	entityOrientation += ROTATION_SPEED;
}

void Player::RotateRight()
{
	entityOrientation -= ROTATION_SPEED;
}

void Player::DrawThrust()
{
	if (m_isThrusting)
	{
		std::vector<Vector2>::iterator it = m_thrusterPoints.begin();
		glBegin(GL_LINE_LOOP);
		for (; it != m_thrusterPoints.end(); it++)
		{
			glVertex2f((*it).x, (*it).y);
		}

		glEnd();
	}
}

void Player::SetThrustingStatus(bool status)
{
	m_isThrusting = status;
}

void Player::Render()
{
	glLoadIdentity();
	glTranslatef(entityPosition.x, entityPosition.y, 0.0f);
	glRotatef(entityOrientation, 0.0f, 0.0f, 1.0f);
	
	//Draw ship
	DrawEntity();

	//Draw thrust 
	DrawThrust();
}