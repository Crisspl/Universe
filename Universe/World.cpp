#include "World.h"

#include <random>
#include <FHL/Graphics/Renderer.h>

#include "OrganismFactory.h"

World::World(fhl::Vec2u _size) :
	m_size(_size),
	m_worldRect(fhl::Vec2f::zero() - fhl::Vec2f::one() * 50.f, fhl::Vec2f(m_size) + fhl::Vec2f::one() * 50.f)
{
}

void World::render(const fhl::RenderConf &) const
{
	for (const Container::value_type & o : m_organisms)
	{
		if (!o->isDead() && m_worldRect.contains(o->getPosition()))
			fhl::Renderer::render(*o);
	}
}

void World::moveHuman(fhl::Vec2f _dir, float _dt)
{
	auto & human = getHuman();
	human.move(_dir * _dt * human.getVelocity());
}

void World::update(float _dt)
{
	removeDeadOrganisms();
	Container newOnes;
	for (Container::value_type & first : m_organisms)
	{
		for (Container::value_type & second : m_organisms)
		{
			if (first->getId() != second->getId() && first->isCollision(*second))
			{
				if (first->isAnimal() && first->getSpecies() == second->getSpecies() && first->isAbleToMultiply() && second->isAbleToMultiply())
				{
					newOnes.push_back(first->multiply());
					first->setAbleToMultiply(false);
					second->setAbleToMultiply(false);
					newOnes.rbegin()->get()->setPosition(first->getPosition() + fhl::Vec2f(Utilities::randomNonZeroVec2i(-100, 100)).normalized() * 100.f);
				}
				else
					first->contact(*second);
			}
		}
		if (first->isPlant() && first->isAbleToMultiply())
		{
			if (auto newOne = first->multiply())
			{
				newOnes.push_back(std::move(newOne));
				newOnes.rbegin()->get()->setPosition(first->getPosition() + fhl::Vec2f(Utilities::randomNonZeroVec2i(-100, 100)).normalized() * 100.f);
			}
			first->setAbleToMultiply(false);
		}
		first->update(_dt);
	}
	m_organisms.reserve(m_organisms.size() + newOnes.size());
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

void World::addRandomOrganism(std::size_t _gener)
{
	const unsigned species = Utilities::random<unsigned>(0, static_cast<unsigned>(Organism::Species::Count) - 1);
	addOrganism(static_cast<Organism::Species>(species), _gener);
}

World::Range World::getSignificantOrganismsRange()
{
	return m_organisms.begin()->get()->isDead() ?
		std::make_pair(std::next(m_organisms.begin()), m_organisms.end()) : std::make_pair(m_organisms.begin(), m_organisms.end());
}

void World::reset()
{
	m_organisms.clear();
	m_organisms.push_back(OrganismFactory::createOrganism(Organism::Species::Human, *this, 0));
}

void World::removeDeadOrganisms()
{
	m_organisms.erase(
		std::remove_if(std::next(m_organisms.begin()), m_organisms.end(), [](const Container::value_type & _o) {return _o->isDead(); }),
		m_organisms.end()
	);
}
