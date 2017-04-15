#include "Plant.h"
#include <type_traits>

Plant::Plant(World & _world, Organism::Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative, std::size_t _gener) :
	Organism(_world, _species, _tex, _str, _initiative, _gener)
{
}

