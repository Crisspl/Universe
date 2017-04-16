#include "Plant.h"

#include "Utilities.h"

Plant::Plant(World & _world, Organism::Species _species, fhl::Texture & _tex, unsigned _str, std::size_t _gener) :
	Organism(_world, _species, _tex, _str, 0u, _gener)
{
}

void Plant::update(float _dt)
{
	addMultiplyTime(_dt);
}

void Plant::contact(Organism & _other)
{
	if (!_other.isPlant())
		_other.attack(*this);
}

void Plant::takeAttack(Organism & _other)
{
	setDead(true);
	Organism::takeAttack(_other);
}

std::unique_ptr<Organism> Plant::multiply() const
{
	if (Utilities::random<unsigned>(0, 99) <= getMultiplyPercentageChance())
		return Organism::multiply();
	return nullptr;
}

