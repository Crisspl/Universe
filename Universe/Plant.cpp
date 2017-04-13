#include "Plant.h"

Plant::Plant(World & _world, Organism::Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative) :
	Organism(_world, _species, _tex, _str, _initiative)
{
}

