#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include <memory>

#include <FHL/Utility/Clock.h>
#include <FHL/Graphics/ColoredRect.h>

#include "World.h"
#include "Camera.h"
#include "srcSolarSystem/Sun.h"

class Game
{
private:
   Game();

public:
   static Game & get();
   void run();
   static void initSystems();

private:
   void mainLoop();
   void handleEvents();
   void update();
   void draw();
	
	void calcCameraRotation();

	void restart();

private:
   static SDL_Window * m_window;
   static SDL_GLContext m_context;

	World m_world;
	Sun m_sun;
	Camera m_cam;

   fhl::Clock m_timer;
   float m_dt;

   bool m_running;
	bool m_handleWorld;

public:
   constexpr static std::size_t WIN_X = 800, WIN_Y = 600;
};

#endif
