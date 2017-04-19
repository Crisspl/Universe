#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"

#include <FHL/Graphics/ResMgr.h>

class Wolf :
	public Animal
{
public:
	Wolf(World & _world, std::size_t _gener) :
		Animal(_world, Organism::Species::Wolf, fhl::ResMgr::loadTexture("wolfTex", "res/wolf.jpg"), 9u, 5u, _gener) {}
};

#endif