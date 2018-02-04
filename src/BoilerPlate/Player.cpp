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
	glVertex2f(0.0 + position.x, 50.0 + position.y);
	glVertex2f(50.0 + position.x, -50.0 + position.y);
	glVertex2f(-50.0 + position.x, -50.0 + position.y);
	glEnd();
}