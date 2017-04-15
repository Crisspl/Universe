#include "Animal.h"

#include <algorithm>

#include "World.h"
#include "Utilities.h"
#include "Sheep.h"

Animal::Animal(World & _world, Organism::Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative, std::size_t _gener) :
	Organism(_world, _species, _tex, _str, _initiative, _gener),
	m_time(0.f)
{
}

void Animal::update(float _dt)
{
	m_time += _dt; //here
	auto targetIter = findTarget();
	if (targetIter == Organism::m_world.getOrganisms().end())
		return;
	fhl::Vec2f target = targetIter->get()->getPosition();
	fhl::Vec2f dir = target - getPosition();
	fhl::Vec2f direction = dir != fhl::Vec2f::zero() ? dir.normalized() : fhl::Vec2f::zero();

	move(getVelocity() * _dt * direction);
}

void Animal::multiply(Organism & _other)
{
	if (m_time < 5.f)
		return; //here
	fhl::Vec2f spawnPosition;
	do
	{
		spawnPosition = 100.f * fhl::Vec2f(static_cast<float>(Utilities::random<int>(-100, 100)), static_cast<float>(Utilities::random<int>(-100, 100)));
	} while (spawnPosition != fhl::Vec2f::zero());
	spawnPosition = spawnPosition.normalized();

	Organism::m_world.addRandomOrganism(std::max(getGeneration(), _other.getGeneration()) + 1);
	m_time = 0.f; //here
}

void Animal::contact(Organism & _other)
{
	if (getSpecies() == _other.getSpecies())
	{
		multiply(_other);
		return;
	}
	Organism::contact(_other);
}

std::vector<std::unique_ptr<Organism>>::iterator Animal::findTarget()
{
	using OrganismPtr = std::unique_ptr<Organism>;

	auto & organisms = Organism::m_world.getOrganisms();
	auto predicate = [this](const OrganismPtr & _a, const OrganismPtr & _b)
		{
			if (_a->getId() == this->getId())
				return false;
			if (_b->getId() == this->getId())
				return true;
			auto distanceA = (this->getPosition() - _a->getPosition()).length();
			auto distanceB = (this->getPosition() - _b->getPosition()).length();
			return distanceA < distanceB;
		};
	return std::min_element(organisms.begin(), organisms.end(), predicate);

}
