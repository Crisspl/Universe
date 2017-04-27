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
#include "srcSolarSystem/EllipseTour.h"

SDL_Window * Game::m_window;
SDL_GLContext Game::m_context;

Game::Game() :
	m_world({WIN_X, WIN_Y}),
	m_sun(fhl::ResMgr::loadModelData("sun", "res/sun/sun.obj")),
	m_cam(fhl::Configurator::getView(fhl::Configurator::getDefaultViewName()).cameraPos),
	m_dt(0.f),
	m_running(true),
	m_handleWorld(true)
{
	restart();
	m_sun.setPosition(fhl::Vec3f(WIN_X / 2, WIN_Y / 2, -200.f));

	auto earth = std::make_unique<Orbitable>(fhl::ResMgr::loadModelData("earth", "res/earth/earth.obj"), std::make_unique<EllipseTour>(400.f, 300.f));
	earth->setScale(m_sun.getScale() * 0.5f);
	auto moon = std::make_unique<Orbitable>(fhl::ResMgr::loadModelData("moon", "res/moon/moon.obj"), std::make_unique<EllipseTour>(120.f, 100.f, 3.f), 500.f);
	moon->setScale(earth->getScale() * 0.3f);
	earth->addSatellite("moon", std::move(moon));

	m_sun.addSatellite("earth", std::move(earth));

	fhl::Configurator::addView("3d", m_cam.getPosition(), m_cam.getCenter(), m_cam.getUpVector());
	fhl::Configurator::setGlobal3DView("3d");
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
	SDL_SetRelativeMouseMode(SDL_TRUE);

   fhl::Configurator::init(WIN_X, WIN_Y);
}

void Game::mainLoop()
{
   while(m_running)
   {
      m_dt = m_timer.restart();

      handleEvents();
      update();
      draw();
   }
   SDL_Quit();
}

void Game::handleEvents()
{
	const Uint8 * kbstate = SDL_GetKeyboardState(NULL);

	if (m_handleWorld)
	{
		if (kbstate[SDL_SCANCODE_UP])
			m_world.moveHuman(fhl::Vec2f::down(), m_dt);
		if (kbstate[SDL_SCANCODE_DOWN])
			m_world.moveHuman(fhl::Vec2f::up(), m_dt);
		if (kbstate[SDL_SCANCODE_LEFT])
			m_world.moveHuman(fhl::Vec2f::left(), m_dt);
		if (kbstate[SDL_SCANCODE_RIGHT])
			m_world.moveHuman(fhl::Vec2f::right(), m_dt);
	}

	if (kbstate[SDL_SCANCODE_W])
		m_cam.move(60.f * m_dt, Camera::MoveDir::Forward);
	if (kbstate[SDL_SCANCODE_S])
		m_cam.move(60.f * m_dt, Camera::MoveDir::Backward);
	if (kbstate[SDL_SCANCODE_A])
		m_cam.move(60.f * m_dt, Camera::MoveDir::Left);
	if (kbstate[SDL_SCANCODE_D])
		m_cam.move(60.f * m_dt, Camera::MoveDir::Right);

	calcCameraRotation();

	fhl::Configurator::setView("3d", m_cam.getPosition(), m_cam.getCenter(), m_cam.getUpVector());

   SDL_Event event;
   while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
				case SDLK_r: restart(); break;
				case SDLK_p:
					if(m_handleWorld)
						m_world.getHuman().activateExtraStrength();
					break;
				case SDLK_q:
					if(m_handleWorld)
						m_world.getHuman().setDead(true);
					break;
				case SDLK_x: m_handleWorld = !m_handleWorld; break;
			}
			break;
		}
   }
}

void Game::update()
{
	if(m_handleWorld)
		m_world.update(m_dt);
	m_sun.update(m_dt);
}

void Game::draw()
{
	fhl::Renderer::clearColor();

	fhl::Configurator::setEnableDepthTest(true);
	fhl::Renderer::render(m_sun);
	fhl::Configurator::setEnableDepthTest(false);

	if(m_handleWorld)
		fhl::Renderer::render(m_world);

   SDL_GL_SwapWindow(m_window);
}

void Game::calcCameraRotation()
{
	static bool firstMouse = true;
	static fhl::Vec2i last = fhl::Vec2i::zero();

	fhl::Vec2f offset;
	fhl::Vec2i current = Input::getMousePosition();

	if (firstMouse)
	{
		firstMouse = false;
		offset = fhl::Vec2f::zero();
	}
	else
		offset = fhl::Vec2f(current.x - last.x, current.y - last.y);

	last = current;

	m_cam.rotate(offset);
}

void Game::restart()
{
	m_world.reset();
	for (int i = 0; i < 50; i++)
		m_world.addRandomOrganism(0);
}
