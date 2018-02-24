#include "App.hpp"
#include <iostream>
#include <algorithm>

// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

namespace Engine
{
	const float DESIRED_FRAME_RATE = 60.0f;
	const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;

	App::App(const std::string& title, const int width, const int height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
		, m_nUpdates(0)
		, m_timer(new TimeManager)
		, m_mainWindow(nullptr)
	{
		m_state = GameState::UNINITIALIZED;
		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();
		m_player = new Player();
		m_asteroidCount = 7;

		CreateAsteroid(m_asteroidCount);
	}

	App::~App()
	{
		if (m_player) 
		{
			delete m_player;
		}
		CleanupSDL();
	}

	void App::CreateAsteroid(int amount)
	{
		srand(time(NULL));

		int currentSize;
		float xCoordinate;
		float yCoordinate;
		float orientation;
		int signChanger = 1; //Used to ensure asteroids will have their initial position in both positive and negative sides of the screen
		
		for (int i = 0; i < amount; i++)
		{
			currentSize = rand() % 3;
			xCoordinate = rand() % 320 + 1 * signChanger;
			yCoordinate = rand() % 568 + 1 * signChanger; 
			orientation = rand() % 360 + 1;


			m_asteroids.push_back(Asteroid((Asteroid::Size)currentSize, xCoordinate, 
				yCoordinate, orientation));

			signChanger *= -1;
		}

		SDL_Log("Current Asteroid count: %i", m_asteroidCount);
	}

	void App::Execute()
	{
		if (m_state != GameState::INIT_SUCCESSFUL)
		{
			std::cerr << "Game INIT was not successful." << std::endl;
			return;
		}

		m_state = GameState::RUNNING;

		SDL_Event event;
		while (m_state == GameState::RUNNING)
		{
			// Input polling
			//
			while (SDL_PollEvent(&event))
			{
				OnEvent(&event);
			}

			//
			Update();
			Render();
		}
	}

	bool App::Init()
	{
		// Init the external dependencies
		//
		bool success = SDLInit() && GlewInit();
		if (!success)
		{
			m_state = GameState::INIT_FAILED;
			return false;
		}

		// Setup the viewport
		//
		SetupViewport();

		// Change game state
		//
		m_state = GameState::INIT_SUCCESSFUL;

		return true;
	}
	
	void App::OnKeyDown(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			SDL_Log("Up key was pressed.");
			m_player->MoveForward();
			break;

		case SDL_SCANCODE_LEFT:
			SDL_Log("Left key was pressed.");
			m_player->RotateLeft();
			break;

		case SDL_SCANCODE_RIGHT:
			SDL_Log("Right key was pressed.");
			m_player->RotateRight();
			break;

		case SDL_SCANCODE_D:
			SDL_Log("D key was pressed.");
			m_player->ShowBoundingCircles(true);
			break;

		case SDL_SCANCODE_A:
			SDL_Log("A key was pressed.");
			CreateAsteroid(1);
			m_asteroidCount++;
			break;

		case SDL_SCANCODE_R:
			SDL_Log("A key was pressed.");
			if (m_asteroidCount > 0) 
			{
				m_asteroids.pop_back();
				m_asteroidCount--;
			}
			SDL_Log("Current Asteroid count: %i", m_asteroidCount);
			break;

		default:
			SDL_Log("% key was pressed.", keyBoardEvent.keysym.scancode);
			break;
		}
	}

	void App::OnKeyUp(SDL_KeyboardEvent keyBoardEvent)
	{
		switch (keyBoardEvent.keysym.scancode)
		{
		case SDL_SCANCODE_ESCAPE:
			OnExit();
			break;

		case SDL_SCANCODE_UP:
			m_player->SetThrustingStatus(false);
			break;
		case SDL_SCANCODE_D:
			m_player->ShowBoundingCircles(false);
			break;
		default:
			//DO NOTHING
			break;
		}
	}

	void App::Update()
	{
		double startTime = m_timer->GetElapsedTimeInSeconds();

		// Update code goes here
		//
		m_player->Update(DESIRED_FRAME_TIME);
		//m_asteroid->Update(DESIRED_FRAME_TIME);

		std::vector<Asteroid>::iterator it = m_asteroids.begin();

		for (; it != m_asteroids.end(); it++)
		{
			(*it).Update(DESIRED_FRAME_TIME);
		}
		double endTime = m_timer->GetElapsedTimeInSeconds();
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

		while (endTime < nextTimeFrame)
		{
			// Spin lock
			endTime = m_timer->GetElapsedTimeInSeconds();
		}

		//double elapsedTime = endTime - startTime;        

		m_lastFrameTime = m_timer->GetElapsedTimeInSeconds();

		m_nUpdates++;
	}

	void App::Render()
	{
		ColorPalette colorPalette;

		glClearColor(colorPalette.NAVY.redValue, colorPalette.NAVY.greenValue,
			colorPalette.NAVY.blueValue, colorPalette.NAVY.alphaValue);

		glClear(GL_COLOR_BUFFER_BIT);

		m_player->Render();
		//m_asteroid->Render();

		std::vector<Asteroid>::iterator it = m_asteroids.begin();

		for (; it != m_asteroids.end(); it++)
		{
			(*it).Render();
		}

		SDL_GL_SwapWindow(m_mainWindow);
	}

	bool App::SDLInit()
	{
		// Initialize SDL's Video subsystem
		//
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cerr << "Failed to init SDL" << std::endl;
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		Uint32 flags = SDL_WINDOW_OPENGL |
			SDL_WINDOW_SHOWN |
			SDL_WINDOW_RESIZABLE;

		m_mainWindow = SDL_CreateWindow(
			m_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_width,
			m_height,
			flags
		);

		if (!m_mainWindow)
		{
			std::cerr << "Failed to create window!" << std::endl;
			SDL_Quit();
			return false;
		}

		m_context = SDL_GL_CreateContext(m_mainWindow);
		SDL_GL_MakeCurrent(m_mainWindow, m_context);

		// Make double buffer interval synced with vertical scanline refresh
		SDL_GL_SetSwapInterval(0);

		return true;
	}

	void App::SetupViewport()
	{
		// Defining ortho values
		//
		float halfWidth = m_width * 0.5f;
		float halfHeight = m_height * 0.5f;

		// Set viewport to match window
		//
		glViewport(0, 0, m_width, m_height);

		// Set Mode to GL_PROJECTION
		//
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set projection MATRIX to ORTHO
		//
		glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1, 1);

		// Setting Mode to GL_MODELVIEW
		//
		glMatrixMode(GL_MODELVIEW);
	}

	bool App::GlewInit()
	{
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return false;
		}

		return true;
	}

	void App::CleanupSDL()
	{
		// Cleanup
		//
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_mainWindow);

		SDL_Quit();
	}

	void App::OnResize(int width, int height)
	{
		// TODO: Add resize functionality
		//
		m_width = width;
		m_height = height;

		SetupViewport();

		m_player->OnWindowResize(m_height, m_width);
	}

	void App::OnExit()
	{
		// Exit main for loop
		//
		m_state = GameState::QUIT;

		// Cleanup SDL pointers
		//
		CleanupSDL();
	}
}