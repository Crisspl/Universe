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
	Container newOnes;
	for (Container::value_type & o : m_organisms)
	{
		for (Container::value_type & other : m_organisms)
		{
			if (o->getId() != other->getId() && o->isCollision(*other))
			{
				if (o->getSpecies() == other->getSpecies() && o->isAbleToMultiply() && other->isAbleToMultiply())
				{
					newOnes.push_back(OrganismFactory::createOrganism(o->getSpecies(), *this, o->getGeneration() + 1));
					o->setAbleToMultiply(false);
					other->setAbleToMultiply(false);
					newOnes.rbegin()->get()->setPosition(o->getPosition() + fhl::Vec2f(Utilities::randomNonZeroVec2i(-100, 100)).normalized() * 100.f);
					// TODO refactor
				}
				else
					o->contact(*other);
			}
		}
		o->update(_dt);
	}
	for(Container::value_type & newOne : newOnes)
		m_organisms.push_back(std::move(newOne));
	std::cout << m_organisms.size() << '\n';
}

void World::addOrganism(Organism::Species _species, std::size_t _gener)
{
	m_organisms.push_back(OrganismFactory::createOrganism(_species, *this, _gener));
	m_organisms.rbegin()->get()->setPosition({
		static_cast<float>(Utilities::random<int>(0, m_size.x)),
		static_cast<float>(Utilities::random<int>(0, m_size.y))
	});
}

void World::addOrganismInRadius(Organism::Species _species, std::size_t _gener, fhl::Vec2f _pos, float _radius)
{
	m_organisms.push_back(OrganismFactory::createOrganism(_species, *this, _gener));
	fhl::Vec2f spawnPosition;
	do
	{
		spawnPosition = fhl::Vec2f(static_cast<float>(Utilities::random<int>(-100, 100)), static_cast<float>(Utilities::random<int>(-100, 100)));
	} while (spawnPosition != fhl::Vec2f::zero());
	spawnPosition = spawnPosition.normalized();
	m_organisms.rbegin()->get()->setPosition(_pos + spawnPosition * _radius);
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
