#include "Player.hpp"
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	position = Vector2();
}

void Player::Update(SDL_KeyboardEvent keyBoardEvent)
{
	switch (keyBoardEvent.keysym.scancode)
	{
	case SDL_SCANCODE_DOWN:
		position.y--;
		break;

	case SDL_SCANCODE_UP:
		position.y++;
		thrusterActivated = true;
		break;

	case SDL_SCANCODE_LEFT:
		position.x--;
		break;

	case SDL_SCANCODE_RIGHT:
		position.x++;
		break;
	default:
		SDL_Log("%S was pressed.", keyBoardEvent.keysym.scancode);
		break;
	}
}

void Player::Render()
{
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0f);
	
	//Draw triangle
	glBegin(GL_LINE_LOOP);
	glVertex2f(0.0, 20.0);
	glVertex2f(12.0, -10.0);
	glVertex2f(6.0, -4.0);
	glVertex2f(-6.0, -4.0);
	glVertex2f(-12.0, -10.0);

	glEnd();

	if (thrusterActivated)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f(6.0, -4.0);
		glVertex2f(-6.0, -4.0);
		glVertex2f(0.0, -14.0);
		glEnd();
	}
}