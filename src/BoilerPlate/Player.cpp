#include "Player.hpp"

const float INITIAL_WINDOW_WIDTH = 1136.0f;
const float INITIAL_WINDOW_HEIGHT = 640.0f ;
const float MOVING_SPEED = 10.0f;
const float ROTATION_SPEED = 10.0f; 
MathUtilities utility;

Player::Player()
{
	playerPosition = new Vector2(Vector2::Origin);
	isThrusting = false;
	playerOrientation = 0.0f;

	minWindowHeight = -INITIAL_WINDOW_HEIGHT / 2;
	maxWindowHeight = -minWindowHeight;
	minWindowWidth = -INITIAL_WINDOW_WIDTH / 2;
	maxWindowWidth = -minWindowWidth;

	ArrangeShipPoints();
	ArrangeThrusterPoints();
}

void Player::ArrangeShipPoints()
{
	shipPoints.push_back(Vector2(0.0f, 20.0f));
	shipPoints.push_back(Vector2(12.0f, -10.0f));
	shipPoints.push_back(Vector2(6.0f, -4.0f));
	shipPoints.push_back(Vector2(-6.0f, -4.0f));
	shipPoints.push_back(Vector2(-12.0f, -10.0f));
}

void Player::ArrangeThrusterPoints()
{
	thrusterPoints.push_back(Vector2(6.0f, -4.0f));
	thrusterPoints.push_back(Vector2(-6.0f, -4.0f));
	thrusterPoints.push_back(Vector2(0.0f, -14.0f));
}

void Player::Update()
{}

float Player::Warp(float coordinate, float min, float max)
{
	if (coordinate < min) return max - (min - coordinate);
	if (coordinate > max) return min + (coordinate - max);
	return coordinate;
}

void Player::OnWindowResize(float newWindowHeight, float newWindowWidth)
{
	minWindowHeight = -newWindowHeight / 2;
	maxWindowHeight = -minWindowHeight;
	minWindowWidth = -newWindowWidth / 2;
	maxWindowWidth = -minWindowWidth;
}

void Player::MoveForward()
{
	playerPosition->x -= MOVING_SPEED * sinf(utility.toRadians(playerOrientation));
	playerPosition->y += MOVING_SPEED * cosf(utility.toRadians(playerOrientation));

	playerPosition->x = Warp(playerPosition->x, minWindowWidth, maxWindowWidth);
	playerPosition->y = Warp(playerPosition->y, minWindowHeight, maxWindowHeight);
}

void Player::RotateLeft()
{
	playerOrientation += ROTATION_SPEED;
}

void Player::RotateRight()
{
	playerOrientation -= ROTATION_SPEED;
}

void Player::DrawShip()
{
	glBegin(GL_LINE_LOOP);
	for(std::vector<Vector2>::iterator it = shipPoints.begin(); 
		it != shipPoints.end(); it++)
	{
		glVertex2f((*it).x, (*it).y);
	}

	glEnd();
}

void Player::DrawThrust()
{
	if (isThrusting)
	{
		glBegin(GL_LINE_LOOP);
		for (std::vector<Vector2>::iterator it = thrusterPoints.begin();
			it != thrusterPoints.end(); it++)
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
	glTranslatef(playerPosition->x, playerPosition->y, 0.0f);
	glRotatef(playerOrientation, 0.0f, 0.0f, 1.0f);
	
	//Draw ship
	DrawShip();

	//Draw thrust 
	DrawThrust();
}