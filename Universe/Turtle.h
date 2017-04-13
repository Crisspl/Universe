#ifndef TURTLE_H
#define TURTLE_H

#include "Animal.h"

#include <FHL/Graphics/ResMgr.h>

class Turtle :
	public Animal
{
public:
	Turtle(World & _world) :
		Animal(_world, Organism::Species::Turtle, fhl::ResMgr::loadTexture("turtleTex", "res/turtle.png"), 2u, 1u) {}

	float getVelocity() const override { return Animal::getVelocity() * 0.25f; }
};

#endif

