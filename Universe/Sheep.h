#ifndef SHEEP_H
#define SHEEP_H

#include "Animal.h"

#include <FHL/Graphics/ResMgr.h>

class Sheep :
	public Animal
{
public:
	Sheep(World & _world) :
		Animal(_world, Organism::Species::Sheep, fhl::ResMgr::loadTexture("sheepTex", "res/sheep.png"), 4u, 4u) {}
};

#endif