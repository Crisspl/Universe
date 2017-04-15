#include "Animal.h"

#include <algorithm>

#include "World.h"
#include "Utilities.h"
#include "Sheep.h"

Animal::Animal(World & _world, Organism::Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative, std::size_t _gener) :
	Organism(_world, _species, _tex, _str, _initiative, _gener)
{
}

void Animal::update(float _dt)
{
	addMultiplyTime(_dt);

	auto targetIter = findTarget();
	if (targetIter == Organism::m_world.getOrganisms().end())
		return;
	fhl::Vec2f target = targetIter->get()->getPosition();
	fhl::Vec2f dir = target - getPosition();
	fhl::Vec2f direction = dir != fhl::Vec2f::zero() ? dir.normalized() : fhl::Vec2f::zero();

	move(getVelocity() * _dt * direction);
}

void Animal::contact(Organism & _other)
{
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
			const float distanceA = (this->getPosition() - _a->getPosition()).length();
			const float distanceB = (this->getPosition() - _b->getPosition()).length();
			//return distanceA < distanceB;
			if (distanceA < distanceB)
			{
				if (_a->getSpecies() == this->getSpecies())
				{
					if (_a->isAbleToMultiply())
						return true;
					else return false;
				}
				else return true;
			}
			else
			{
				if (_b->getSpecies() == this->getSpecies())
				{
					if (_b->isAbleToMultiply())
						return false;
					else return true;
				}
				else return false;
			}
		};
	return std::min_element(organisms.begin(), organisms.end(), predicate);

}
