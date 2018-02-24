#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Vector2.hpp"
#include "MathUtilities.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

class Entity
{
public:
	/*CTOR*/
	Entity();

	/*PUBLIC FUNCTIONS*/
	virtual void Update(float);
	virtual void Render(void);
	void DrawEntity(void);
	void OnWindowResize(float, float);
	virtual void ArrangeEntityPoints(void);
	float Warp(float, float, float);
	virtual void ApplyImpulse(Vector2 impulse);
	void DrawBoundingCircle(void);
	void ShowBoundingCircles(bool);

protected:
	/*PRIVATE MEMBERS*/
	Vector2 m_entityPosition;
	Vector2 m_entityVelocity;
	float m_entityOrientation;
	float m_entityMass;
	MathUtilities m_utility;
	float m_entityRadius;
	bool m_showingCircles;

	float m_minWindowHeight;
	float m_maxWindowHeight;
	float m_minWindowWidth;
	float m_maxWindowWidth;

	std::vector<Vector2> m_entityPoints;
};

#endif // !_ENTITY_H_

