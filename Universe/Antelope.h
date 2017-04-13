#ifndef ANTELOPE_H
#define ANTELOPE_H

#include "Animal.h"

#include <FHL/Graphics/ResMgr.h>

class Antelope :
	public Animal
{
public:
	Antelope(World & _world) :
		Animal(_world, Organism::Species::Antelope, fhl::ResMgr::loadTexture("antelopeTex", "res/antelope.png"), 4u, 4u) {}

	float getVelocity() const override { return Animal::getVelocity() * 2.f; }
};

#endif

