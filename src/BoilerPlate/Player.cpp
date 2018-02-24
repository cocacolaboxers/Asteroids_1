#include "Player.hpp"
const float MOVING_SPEED = 10.0f;
const float ROTATION_SPEED = 10.0f; 
const float DESIRED_MAX_SPEED = 300.0f;
const float FRICTION_FORCE = 0.999F; //Proportion?

Player::Player()
{
	m_isThrusting = false;
	ArrangeEntityPoints();
	ArrangeThrusterPoints();
	entityRadius = 15.0f; //*Hardcoded* (Ship's highest + lowest points (diameter) / 2
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
		entityVelocity.x = utility.Clamp(entityVelocity.x, -DESIRED_MAX_SPEED, DESIRED_MAX_SPEED);
		entityVelocity.y = utility.Clamp(entityVelocity.y, -DESIRED_MAX_SPEED, DESIRED_MAX_SPEED);
	}

	//Because friction is a thing that exists... TODO: TURN INTO A FUNCTION?
	entityVelocity.x *= FRICTION_FORCE;
	entityVelocity.y *= FRICTION_FORCE;
	
	Entity::Update(deltaTime);
}

void Player::MoveForward()
{
	m_isThrusting = true;
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

	//Draw Bounding circle
	DrawBoundingCircle();
}