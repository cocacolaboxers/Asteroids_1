#include "App.hpp"
#include <iostream>
#include <algorithm>


// OpenGL includes
#include <GL/glew.h>
#include <SDL_opengl.h>


namespace Engine
{
	const float DESIRED_FRAME_RATE = 60.0f;
	const float DESIRED_FRAME_TIME = 1.0f / DESIRED_FRAME_RATE;
	const float ROTATING_SPEED = 50.0f;
	const int MAX_ANGLE_IN_DEGREES = 360;
	const float X_AXIS_POSITION = 300.0f;
	const float Y_AXIS_POSITION = -300.0f;
	const int MAX_RECORDED_FRAME_COUNT = 10;
	const float X_AXIS_SCALE = 10.0f;
	const float Y_AXIS_SCALE = 100000.0f;
	const int SMALL_ASTEROID_COLLISION_SCORE = 20;
	const int MEDIUM_ASTEROID_COLLISION_SCORE = 20;
	const int BIG_ASTEROID_COLLISION_SCORE = 20;
	const int COOLING_PERIOD_IN_SECONDS = 2; //For this period of time the player can't die or shoot
	std::vector<Vector2> playerShipPoints;
	const float SEPARATION_DISTANCE = 10; 


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
		m_asteroidCount = 5;
		m_initialAseroidCount = m_asteroidCount;
		m_showingFramePlot = false;
		m_deltaTime = DESIRED_FRAME_TIME;

		m_entities.push_back(m_player);
		CreateAsteroid(m_asteroidCount);
		SDL_Log("Current bullet count: %i", m_bullets.size());

		m_currentFramePositionInVector = 0;
		m_capturedFrames = std::vector<Vector2>(MAX_RECORDED_FRAME_COUNT);

		for (int i = 0; i < m_capturedFrames.size(); i++)
		{
			m_capturedFrames[i] = Vector2(i, DESIRED_FRAME_TIME);
		}

		m_scorePoints = 0;

		m_remainingLives = 3;

		playerShipPoints = m_player->GetEntityPoints();
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
			currentSize = rand() % ((int)Asteroid::Size::SMALL + 1);
			xCoordinate = rand() % (m_width/2) * signChanger;
			yCoordinate = rand() % (m_height/2) * signChanger; 
			orientation = rand() % MAX_ANGLE_IN_DEGREES;

			Asteroid* currentAsteroid = new Asteroid((Asteroid::Size)currentSize, xCoordinate,
				yCoordinate, orientation);

			m_asteroids.push_back(currentAsteroid);
			m_asteroidCount++;
			m_entities.push_back(currentAsteroid);

			signChanger *= -1;
		}

		SDL_Log("Current Asteroid count: %i", m_asteroidCount);
	}

	void App::RemoveAsteroid(void)
	{
		if (m_asteroidCount > 0)
		{
			m_asteroids.pop_back();
			m_asteroidCount--;
		}
	}

	void App::RespawnPlayer()
	{
		m_remainingLives--;
		if (m_remainingLives > 0) {
			m_player = new Player();
			m_entities.push_back(m_player);
		}
		SDL_Log("Current life count: %i", m_remainingLives);
	}

	void App::DrawRemainingLives(void)
	{
		for (int i = 0; i < m_remainingLives; i++)
		{

		}
	}

	void App::DrawLinesToNearbyAsteroids()
	{
		if (m_player->GetDebuggingStatus() && !m_player->GetCollisionStatus())
		{
			Vector2 playerPosition = m_player->GetPosition();
			Vector2 positionOfCurrentAsteroid;
			float proximityMeasurement = (m_player->GetRadius()) * 2.0f;
			float radiusOfCurrentAsteroid;
			float distance;
			float aproximateDistanceToBoundingCircle;

			glLoadIdentity();
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < m_asteroids.size(); i++)
			{
				positionOfCurrentAsteroid = (*m_asteroids[i]).GetPosition();
				radiusOfCurrentAsteroid = (*m_asteroids[i]).GetRadius();
				distance = m_player->CalculateDistanceBetweenEntities((*m_asteroids[i]));

				//Take into consideration the Asteroid's radius
				aproximateDistanceToBoundingCircle = proximityMeasurement + radiusOfCurrentAsteroid;

				if (distance <= aproximateDistanceToBoundingCircle) 
				{
					glColor3f(m_colorPalette.RED.redValue, m_colorPalette.RED.blueValue, m_colorPalette.RED.greenValue); //Make line red
					glVertex2f(playerPosition.x, playerPosition.y);
					glVertex2f(positionOfCurrentAsteroid.x, positionOfCurrentAsteroid.y);
				}

				//Reset color to white
				glColor4f(m_colorPalette.WHITE.redValue, m_colorPalette.WHITE.blueValue, m_colorPalette.WHITE.greenValue, m_colorPalette.WHITE.alphaValue);
			}
			glEnd();
		}
	}

	void App::OnAsteroidCollision()
	{
		for (int i = 0; i < m_asteroids.size(); i++)
		{
			if (!m_player->GetCollisionStatus() && !(*m_asteroids[i]).GetCollisionStatus())
			{
				if (m_player->DetectCollision(*m_asteroids[i]))
				{
					if(!m_player->GetDebuggingStatus())
						RespawnPlayer();
				}
			}
		}
	}

	void App::OnBulletCollision(void)
	{
		for (int i = 0; i < m_asteroids.size(); i++)
		{
			for (int j = 0; j < m_bullets.size(); j++)
			{
				if (m_asteroids[i]->DetectCollision(*m_bullets[j]))
				{
					//When bullets collide with asteroids they should split them in smaller halves
					if (m_asteroids[i]->GetSize() == Asteroid::Size::BIG)
					{
						m_scorePoints += BIG_ASTEROID_COLLISION_SCORE;

						Vector2 originalPosition = m_asteroids[i]->GetPosition();
						float originalOrientaion = m_asteroids[i]->GetOrientation();

						Asteroid* firstChild = new Asteroid(Asteroid::Size::MEDIUM, originalPosition.x, 
							originalPosition.y, originalOrientaion);

						Asteroid* secondChild = new Asteroid(Asteroid::Size::MEDIUM, originalPosition.x,
							originalPosition.y, originalOrientaion + ROTATING_SPEED);

						m_asteroids.push_back(firstChild);
						m_entities.push_back(firstChild);

						m_asteroids.push_back(secondChild);
						m_entities.push_back(secondChild);

						m_bullets[j]->SetDisappearanceStatus(true);
						m_bullets.erase(m_bullets.begin() + j); //Delete bullet
						m_asteroids.erase(m_asteroids.begin() + i); //Delete parent Asteroid
						m_asteroidCount++;
					}

					else if (m_asteroids[i]->GetSize() == Asteroid::Size::MEDIUM)
					{
						m_scorePoints += MEDIUM_ASTEROID_COLLISION_SCORE;

						Vector2 originalPosition = m_asteroids[i]->GetPosition();
						float originalOrientaion = m_asteroids[i]->GetOrientation();

						Asteroid* firstChild = new Asteroid(Asteroid::Size::SMALL, originalPosition.x,
							originalPosition.y, originalOrientaion);

						Asteroid* secondChild = new Asteroid(Asteroid::Size::SMALL, originalPosition.x,
							originalPosition.y, originalOrientaion + ROTATING_SPEED);

						m_asteroids.push_back(firstChild);
						m_entities.push_back(firstChild);

						m_asteroids.push_back(secondChild);
						m_entities.push_back(secondChild);

						m_bullets[j]->SetDisappearanceStatus(true);
						m_bullets.erase(m_bullets.begin() + j); //Delete bullet
						m_asteroids.erase(m_asteroids.begin() + i); //Delete parent Asteroid
						m_asteroidCount++;
					}

					else if (m_asteroids[i]->GetSize() == Asteroid::Size::SMALL)
					{
						m_scorePoints += SMALL_ASTEROID_COLLISION_SCORE;
						m_bullets[j]->SetDisappearanceStatus(true);
						m_bullets.erase(m_bullets.begin() + j); //Delete bullet
						m_asteroids.erase(m_asteroids.begin() + i); //Delete parent Asteroid
						m_asteroidCount++;
					}

					break; //Stop evaluating after a collision is detected
				}
				else
				{
					if(m_bullets[j]->GetDisappearanceStatus())
						m_bullets.erase(m_bullets.begin() + j); //Delete bullet that has disappeared and not collided
				}
			}
		}
	}

	void App::UpdateFrameSequence(void)
	{
		m_capturedFrames[m_currentFramePositionInVector] = Vector2((float)m_currentFramePositionInVector, m_deltaTime);
		m_currentFramePositionInVector++;

		if (m_currentFramePositionInVector >= MAX_RECORDED_FRAME_COUNT)
			m_currentFramePositionInVector = 0;
	}

	void App::PlotFrameRate(void)
	{
		glColor4f(m_colorPalette.WHITE.redValue, m_colorPalette.WHITE.greenValue, m_colorPalette.WHITE.blueValue, m_colorPalette.WHITE.alphaValue);
		glLoadIdentity();
		//Locate in window
		glTranslatef(X_AXIS_POSITION, Y_AXIS_POSITION, 0.0f);
		glBegin(GL_LINE_STRIP);
		glVertex2f(0.0f, 100.0f); //Draw Y axis
		glVertex2f(0.0f, 0.0f); //Set vertex of cartesian plane;
		glVertex2f(130.0f, 0.0f); //Draw X axis
		glEnd();

		glBegin(GL_LINE_STRIP);
		//glColor4f(m_colorPalette.WHITE.redValue, m_colorPalette.WHITE.greenValue, m_colorPalette.WHITE.blueValue, m_colorPalette.WHITE.alphaValue);
		for (int i = 0; i < MAX_RECORDED_FRAME_COUNT; i++)
		{
			glVertex2f(X_AXIS_SCALE * m_capturedFrames[i].x, Y_AXIS_SCALE * (DESIRED_FRAME_TIME - m_capturedFrames[i].y));
		}
		glEnd();
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

		if (TTF_Init() == -1) {
			SDL_Log("TTF_Init: %s\n", TTF_GetError());
			return false;
		}

		SDL_version compile_version;
		const SDL_version *link_version = TTF_Linked_Version();
		SDL_TTF_VERSION(&compile_version);

		SDL_Log("compiled with SDL_ttf version: %d.%d.%d\n",
			compile_version.major,
			compile_version.minor,
			compile_version.patch); 

		SDL_Log("running with SDL_ttf version: %d.%d.%d\n",
			link_version->major,
			link_version->minor,
			link_version->patch);

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
		{
			SDL_Log("D key was pressed.");

			for (int i = 0; i < m_entities.size(); i++)
			{
				m_entities[i]->ToggleDebuggingFeatures(true);
			}
		}
			break;

		case SDL_SCANCODE_A:
			SDL_Log("A key was pressed.");
			CreateAsteroid(1);
			m_asteroidCount++;
			break;

		case SDL_SCANCODE_R:
			SDL_Log("R key was pressed.");
			RemoveAsteroid();
			break;

		case SDL_SCANCODE_F:
			SDL_Log("F key was pressed.");
			m_showingFramePlot = true;
			break;

		case SDL_SCANCODE_SPACE: {
			SDL_Log("Space key was pressed.");
			Bullet* currentBullet = m_player->Shoot();
			m_bullets.push_back(currentBullet); 
			m_entities.push_back(currentBullet);
			SDL_Log("Current bullet count: %i", m_bullets.size());
			SDL_Log("Current entity count: %i", m_entities.size());
		}
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

		case SDL_SCANCODE_F:
			m_showingFramePlot = false;
			break;

		case SDL_SCANCODE_D:
		{
			for (int i = 0; i < m_entities.size(); i++)
			{
				m_entities[i]->ToggleDebuggingFeatures(false);
			}
		}
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
		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->Update(m_deltaTime);
		}

		//Add asteroids as the game progresses
		if (m_asteroids.size() == 0)
			CreateAsteroid(++m_initialAseroidCount);

		OnAsteroidCollision();
		OnBulletCollision();

		double endTime = m_timer->GetElapsedTimeInSeconds();
		double nextTimeFrame = startTime + DESIRED_FRAME_TIME;

		m_deltaTime = DESIRED_FRAME_TIME - (endTime-startTime);
		UpdateFrameSequence();

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
		glClearColor(m_colorPalette.NAVY.redValue, m_colorPalette.NAVY.greenValue,
			m_colorPalette.NAVY.blueValue, m_colorPalette.NAVY.alphaValue);

		glClear(GL_COLOR_BUFFER_BIT);

		RenderEntities();

		DrawLinesToNearbyAsteroids();

		if(m_showingFramePlot)
			PlotFrameRate();

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
		TTF_Quit();
	}

	void App::OnResize(int width, int height)
	{
		// TODO: Add resize functionality
		//
		m_width = width;
		m_height = height;

		SetupViewport();

		WarpEntities(m_height, m_width);
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

	void App::RenderEntities()
	{
		//Used to render all entities altogether. Renderization by using m_entities vector does work properly when deleting asteroids
		m_player->Render();
		for (int i = 0; i < m_asteroids.size(); i++)
		{
			m_asteroids[i]->Render();
		}

		for (int i = 0; i < m_bullets.size(); i++)
		{
			m_bullets[i]->Render();
		}
	}

	void App::WarpEntities(float newHeight, float newWidth)
	{
		for (int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->OnWindowResize(newHeight, newWidth);
		}
	}

} 