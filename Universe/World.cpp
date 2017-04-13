#include "World.h"

#include <random>

#include <FHL/Graphics/Renderer.h>

World::World()
{
}

void World::render(const fhl::RenderConf &) const
{
	for (const Container::value_type & o : m_organisms)
		fhl::Renderer::render(*o);
}

void World::update(float _dt)
{
	for (const Container::value_type & o : m_organisms)
	{
		o->update(_dt);
		//std::cout << o->getPosition() << '\n';
	}

}

void World::addOrganism(std::unique_ptr<Organism> && _org)
{
	m_organisms.push_back(std::move(_org));
	m_organisms.rbegin()->get()->setPosition({ float(rand() % 800), float(rand() % 600) });
}
