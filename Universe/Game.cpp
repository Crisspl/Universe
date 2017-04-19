#include "Game.h"

#include <FHL/Graphics/Configurator.h>
#include <FHL/Graphics/ResMgr.h>
#include <FHL/Graphics/Renderer.h>

#include "Input.h"

#include "Antelope.h"
#include "Turtle.h"
#include "Fox.h"
#include "Wolf.h"
#include "Sheep.h"

SDL_Window * Game::m_window;
SDL_GLContext Game::m_context;

Game::Game() :
	m_world({WIN_X, WIN_Y}),
	m_running(true)
{
	restart();
}

Game & Game::get()
{
   static Game instance;
   return instance;
}

void Game::run()
{
   mainLoop();
}

void Game::initSystems()
{
   SDL_Init(SDL_INIT_EVERYTHING);

   m_window = SDL_CreateWindow(
                 "Universe",
                 SDL_WINDOWPOS_UNDEFINED,
                 SDL_WINDOWPOS_UNDEFINED,
                 WIN_X,
                 WIN_Y,
                 SDL_WINDOW_OPENGL
             );
   m_context = SDL_GL_CreateContext(m_window);

   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
   SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

   SDL_GL_SetSwapInterval(1);

   fhl::Configurator::init(WIN_X, WIN_Y);
}

void Game::mainLoop()
{
   while(m_running)
   {
      dt = m_timer.restart();

      handleEvents();
      update();
      draw();
   }
   SDL_Quit();
}

void Game::handleEvents()
{
	static std::map<unsigned, fhl::Vec2f> dirs
	{
		std::make_pair(SDLK_UP, fhl::Vec2f::down()),
		std::make_pair(SDLK_DOWN, fhl::Vec2f::up()),
		std::make_pair(SDLK_LEFT, fhl::Vec2f::left()),
		std::make_pair(SDLK_RIGHT, fhl::Vec2f::right())
	};

   SDL_Event event;
	const Uint8 * kbstate = SDL_GetKeyboardState(NULL);
	if (kbstate[SDL_SCANCODE_UP])
		m_world.moveHuman(fhl::Vec2f::down(), dt);
	if (kbstate[SDL_SCANCODE_DOWN])
		m_world.moveHuman(fhl::Vec2f::up(), dt);
	if (kbstate[SDL_SCANCODE_LEFT])
		m_world.moveHuman(fhl::Vec2f::left(), dt);
	if (kbstate[SDL_SCANCODE_RIGHT])
		m_world.moveHuman(fhl::Vec2f::right(), dt);

   while (SDL_PollEvent(&event)) { 
		switch (event.type) {
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_r: restart(); break;
				case SDLK_p: m_world.activateHumanSuperpower(); break;
			}
			break;
		}
   }
}

void Game::update()
{
	m_world.update(dt);
}

void Game::draw()
{
	fhl::Renderer::clearColor();

	fhl::Renderer::render(m_world);

   SDL_GL_SwapWindow(m_window);
}

void Game::restart()
{
	m_world.reset();
	for (int i = 0; i < 50; i++)
		m_world.addRandomOrganism(0);
}
