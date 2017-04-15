#include "World.h"

#include <random>
#include <FHL/Graphics/Renderer.h>

#include "Utilities.h"
#include "Antelope.h"
#include "CyberSheep.h"
#include "Fox.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"

std::array<World::AddFunc_t, 6> World::s_addFunctions{ {
		&World::addOrganism<Antelope>,
		&World::addOrganism<CyberSheep>,
		&World::addOrganism<Fox>,
		&World::addOrganism<Sheep>,
		&World::addOrganism<Turtle>,
		&World::addOrganism<Wolf>
} };

World::World(fhl::Vec2u _size) : m_size(_size)
{
}

void World::render(const fhl::RenderConf &) const
{
	for (const Container::value_type & o : m_organisms)
		fhl::Renderer::render(*o);
}

void World::update(float _dt)
{
	removeDeadOrganisms();
	for (Container::value_type & o : m_organisms)
	{
		for (Container::value_type & other : m_organisms)
		{
			if (o->getId() != other->getId() && o->isCollision(*other))
				o->contact(*other);
		}
		o->update(_dt);
	}
}

void World::addRandomOrganism(std::size_t _gener)
{
	const unsigned n = Utilities::random<unsigned>(0, s_addFunctions.size() - 1);
	(this->*s_addFunctions[n])(_gener);
}

void World::removeDeadOrganisms()
{
	m_organisms.erase(
		std::remove_if(m_organisms.begin(), m_organisms.end(), [](const Container::value_type & _o) {return _o->isDead(); }),
		m_organisms.end()
	);
}
