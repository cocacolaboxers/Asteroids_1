#pragma once
#ifndef APP_HPP
#define APP_HPP

// C++ STL
#include <string>
#include <list>
#include <vector>
#include <cstdlib>
#include <ctime>

// Asteroids
#include "SDLEvent.hpp"
#include "TimeManager.hpp"

//New classes includes
#include "Color.hpp"
#include "ColorPalette.hpp"
#include "MathUtilities.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Bullet.hpp"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

namespace Engine
{
	class App : public SDLEvent
	{
	public:
		/* =============================================================
		* ENUMERATORS
		* ============================================================= */
		struct GameState
		{
			enum State
			{
				UNINITIALIZED = 0,
				INIT_FAILED = 1,
				INIT_SUCCESSFUL = 2,
				RUNNING = 4,
				PAUSED = 8,
				QUIT = 16
			};
		};

		/* =============================================================
		 * PUBLIC FUNCTIONS
		 * ============================================================= */
		App( const std::string& title, const int width, const int height );
		~App( );
		void Execute						( );
		bool Init							( );
		void Update							( );
		void Render							( );
	private:
		/* =============================================================
		 * PRIVATE FUNCTIONS
		 * ============================================================= */
		bool SDLInit							( );
		bool GlewInit						( );
		void SetupViewport					( );
		void CleanupSDL						( );
		void OnResize						( int width, int height ) override;
		void OnExit							( ) override;
		void OnKeyDown						( SDL_KeyboardEvent keyBoardEvent ) override;
		void OnKeyUp							( SDL_KeyboardEvent keyBoardEvent ) override;
		void CreateAsteroid					(int);
		void RemoveAsteroid					(void);
		void DrawLinesToNearbyAsteroids		(void);
		void OnAsteroidCollision				(void);
		void OnBulletCollision				(void);
		void UpdateFrameSequence				(void);
		void PlotFrameRate					(void);
		void RenderEntities					(void);
		void WarpEntities					(float, float);

		/* =============================================================
		 * MEMBERS
		 * ============================================================= */
		int									m_width;
		int									m_height;
		int									m_nUpdates;
		double								m_lastFrameTime;
		std::string							m_title;
		SDL_Window*							m_mainWindow;
		SDL_GLContext						m_context;
		GameState::State						m_state;
		Engine::TimeManager*					m_timer;
		Player*								m_player;
		std::vector<Asteroid*>				m_asteroids;
		std::vector<Bullet*>					m_bullets;
		int									m_asteroidCount;
		std::vector<Entity*>					m_entities;
		ColorPalette							m_colorPalette;
		float								m_deltaTime;
		std::vector<Vector2>					m_capturedFrames;
		int									m_currentFramePositionInVector;
		bool									m_showingFramePlot;
		bool									m_scorePoints;
	};
}
#endif /* GAME_HPP */
