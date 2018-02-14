#include "Player.hpp"
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

const float initialWindowWidth = 1136.0f;
const float initialWindowHeight = 640.0f ;

Player::Player()
{
	playerPosition = new Vector2(Vector2::Origin);
	isThrusting = false;
	playerOrientation = 0.0f;

	minWindowHeight = -initialWindowHeight / 2;
	maxWindowHeight = -minWindowHeight;
	minWindowWidth = -initialWindowWidth / 2;
	maxWindowWidth = -minWindowWidth;
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
	MathUtilities utility;

	playerPosition->x -= 10 * sinf(utility.toRadians(playerOrientation));
	playerPosition->y += 10 * cosf(utility.toRadians(playerOrientation));

	playerPosition->x = Warp(playerPosition->x, minWindowWidth, maxWindowWidth);
	playerPosition->y = Warp(playerPosition->y, minWindowHeight, maxWindowHeight);
}

void Player::RotateLeft()
{
	playerOrientation += 10;
}

void Player::RotateRight()
{
	playerOrientation -= 10;
}

void Player::DrawShip()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 20.0);
	glVertex2f(12.0, -10.0);
	glVertex2f(6.0, -4.0);
	glVertex2f(-6.0, -4.0);
	glVertex2f(-12.0, -10.0);
	glEnd();
}

void Player::setThrustingStatus(bool status)
{
	isThrusting = status;
}

void Player::DrawThrust()
{
	if (isThrusting)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(6.0, -4.0);
		glVertex2f(-6.0, -4.0);
		glVertex2f(0.0, -14.0);
		glEnd();
	}
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