#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Vector2.hpp"
#include "MathUtilities.hpp"
#include <vector>

// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

class Entity
{
public:
	/*CTOR*/
	Entity();

	/*PUBLIC FUNCTIONS*/
	virtual void Update(void);
	virtual void Render(void);
	virtual void MoveForward(void);
	void DrawEntity(void);
	void OnWindowResize(float, float);
	virtual void ArrangeEntityPoints(void);
	float Warp(float, float, float);

protected:
	/*PRIVATE MEMBERS*/
	Vector2 * entityPosition;
	float entityOrientation;
	float entityMass;

	float minWindowHeight;
	float maxWindowHeight;
	float minWindowWidth;
	float maxWindowWidth;

	std::vector<Vector2> entityPoints;

};

#endif // !_ENTITY_H_

