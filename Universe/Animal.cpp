#include "Animal.h"

#include <algorithm>

#include "World.h"

Animal::Animal(World & _world, Organism::Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative)
	: Organism(_world, _species, _tex, _str, _initiative)
{
}

void Animal::update(float _dt)
{
	auto targetIter = findTarget();
	if (targetIter == Organism::m_world.getOrganisms().end())
		return;
	fhl::Vec2f target = targetIter->get()->getPosition();
	fhl::Vec2f pos = getPosition();
	fhl::Vec2f direction = (target - pos).normalized();

	//std::cout << "target: " << target << '\n';
	move(getVelocity() * _dt * direction);
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
