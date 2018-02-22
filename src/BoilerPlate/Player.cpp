#include "Player.hpp"

const float INITIAL_WINDOW_WIDTH = 1136.0f;
const float INITIAL_WINDOW_HEIGHT = 640.0f ;
const float MOVING_SPEED = 10.0f;
const float ROTATION_SPEED = 10.0f; 
MathUtilities utility;

Player::Player()
{
	isThrusting = false;

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
	thrusterPoints.push_back(Vector2(6.0f, -4.0f));
	thrusterPoints.push_back(Vector2(-6.0f, -4.0f));
	thrusterPoints.push_back(Vector2(0.0f, -14.0f));
}

void Player::Update(float deltaTime)
{
	Entity::Update(deltaTime);
}

void Player::MoveForward()
{
	entityPosition.x -= MOVING_SPEED * sinf(utility.toRadians(entityOrientation));
	entityPosition.y += MOVING_SPEED * cosf(utility.toRadians(entityOrientation));

	entityPosition.x = Warp(entityPosition.x, minWindowWidth, maxWindowWidth);
	entityPosition.y = Warp(entityPosition.y, minWindowHeight, maxWindowHeight);
}

void Player::RotateLeft()
{
	entityOrientation += ROTATION_SPEED;
}

void Player::RotateRight()
{
	entityOrientation -= ROTATION_SPEED;
}

void Player::ApplyImpulse(Vector2 impulse)
{
	if (entityMass > 0)
	{
		entityVelocity.x += (impulse.x / entityMass) * cosf(utility.toRadians(entityOrientation));
		entityVelocity.y += (impulse.y / entityMass) * cosf(utility.toRadians(entityOrientation));
	}
}

void Player::DrawThrust()
{
	if (isThrusting)
	{
		std::vector<Vector2>::iterator it = thrusterPoints.begin();
		glBegin(GL_LINE_LOOP);
		for (; it != thrusterPoints.end(); it++)
		{
			glVertex2f((*it).x, (*it).y);
		}

		glEnd();
	}
}

void Player::SetThrustingStatus(bool status)
{
	isThrusting = status;
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