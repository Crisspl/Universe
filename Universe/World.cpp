#include "World.h"

#include <random>
#include <FHL/Graphics/Renderer.h>

#include "OrganismFactory.h"

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

void World::addOrganism(Organism::Species _species, std::size_t _gener)
{
	m_organisms.push_back(OrganismFactory::createOrganism(_species, *this, _gener));
	m_organisms.rbegin()->get()->setPosition({
		static_cast<float>(Utilities::random<int>(0, m_size.x)),
		static_cast<float>(Utilities::random<int>(0, m_size.y))
	});
}

void World::addRandomOrganism(std::size_t _gener)
{
	const unsigned species = Utilities::random<unsigned>(0, static_cast<unsigned>(Organism::Species::Wolf));
	addOrganism(static_cast<Organism::Species>(species), _gener);
}

void World::removeDeadOrganisms()
{
	m_organisms.erase(
		std::remove_if(m_organisms.begin(), m_organisms.end(), [](const Container::value_type & _o) {return _o->isDead(); }),
		m_organisms.end()
	);
}
