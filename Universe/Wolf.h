#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"

#include <FHL/Graphics/ResMgr.h>

class Wolf :
	public Animal
{
public:
	Wolf(World & _world) :
		Animal(_world, Organism::Species::Wolf, fhl::ResMgr::loadTexture("wolfTex", "res/wolf.png"), 9u, 5u) {}
};

#endif