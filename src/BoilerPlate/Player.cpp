#include "Player.hpp"
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	playerPosition = new Vector2();
	thrusterActivated = false;
}

void Player::Update()
{}

void Player::Move(const Vector2& unit) {
	playerPosition->x += unit.x;
	playerPosition->y += unit.y;
}

void Player::Warp()
{}

void Player::MoveForward()
{}

void Player::RotateLeft()
{}

void Player::RotateRight()
{}

void Player::Render()
{
	glLoadIdentity();
	glTranslatef(playerPosition->x, playerPosition->y, 0.0f);
	
	//Draw ship
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 20.0);
	glVertex2f(12.0, -10.0);
	glVertex2f(6.0, -4.0);
	glVertex2f(-6.0, -4.0);
	glVertex2f(-12.0, -10.0);

	glEnd();

	//Draw thrust 
	if (thrusterActivated)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(6.0, -4.0);
		glVertex2f(-6.0, -4.0);
		glVertex2f(0.0, -14.0);
		glEnd();
	}
}