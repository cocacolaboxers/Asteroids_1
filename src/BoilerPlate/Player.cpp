#include "Player.hpp"
const float MOVING_SPEED = 10.0f;
const float ROTATION_SPEED = 10.0f; 
const float DESIRED_MAX_SPEED = 300.0f;
const float FRICTION_FORCE = 0.999F;

Player::Player()
{
	m_isThrusting = false;
	ArrangeEntityPoints();
	ArrangeThrusterPoints();
	m_entityRadius = 19.5f;
}

void Player::ArrangeEntityPoints()
{
	m_entityPoints.push_back(Vector2(0.0f, 20.0f));
	m_entityPoints.push_back(Vector2(12.0f, -10.0f));
	m_entityPoints.push_back(Vector2(6.0f, -4.0f));
	m_entityPoints.push_back(Vector2(-6.0f, -4.0f));
	m_entityPoints.push_back(Vector2(-12.0f, -10.0f));
}

void Player::ArrangeThrusterPoints()
{
	m_thrusterPoints.push_back(Vector2(6.0f, -4.0f));
	m_thrusterPoints.push_back(Vector2(-6.0f, -4.0f));
	m_thrusterPoints.push_back(Vector2(0.0f, -14.0f));
}

void Player::Update(float deltaTime)
{
	m_playerCurrentSpeed = std::fabs(m_entityVelocity.Length());
	if(m_playerCurrentSpeed > DESIRED_MAX_SPEED)
	{
		m_entityVelocity.x = m_utility.Clamp(m_entityVelocity.x, -DESIRED_MAX_SPEED, DESIRED_MAX_SPEED);
		m_entityVelocity.y = m_utility.Clamp(m_entityVelocity.y, -DESIRED_MAX_SPEED, DESIRED_MAX_SPEED);
	}

	//Have friction affect the ship's velocity
	m_entityVelocity.x *= FRICTION_FORCE;
	m_entityVelocity.y *= FRICTION_FORCE;
	
	Entity::Update(deltaTime);
}

void Player::MoveForward()
{
	m_isThrusting = true;
	ApplyImpulse(Vector2(MOVING_SPEED, MOVING_SPEED));
}
 
void Player::RotateLeft()
{
	m_entityOrientation += ROTATION_SPEED;
}

void Player::RotateRight()
{
	m_entityOrientation -= ROTATION_SPEED;
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
	glTranslatef(m_entityPosition.x, m_entityPosition.y, 0.0f);
	glRotatef(m_entityOrientation, 0.0f, 0.0f, 1.0f);
	
	//Draw ship
	DrawEntity();

	//Draw thrust 
	DrawThrust();

	//Draw Bounding circle
	DrawBoundingCircle();
}