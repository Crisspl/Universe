#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <SDL.h>
#include <vector>
#include <memory>

#include <FHL/Utility/Clock.h>
#include <FHL/Graphics/ColoredRect.h>

#include "World.h"

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

	void restart();

private:
   static SDL_Window * m_window;
   static SDL_GLContext m_context;

	World m_world;

   fhl::Clock m_timer;
   float dt;

   bool m_running;

public:
   constexpr static std::size_t WIN_X = 800, WIN_Y = 600;
};

#endif
