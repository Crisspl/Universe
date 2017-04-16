#ifndef GRASS_H
#define GRASS_H

#include "Plant.h"

#include <FHL/Graphics/ResMgr.h>

class Grass :
	public Plant
{
public:
	Grass(World & _w, std::size_t _gener) :
		Plant(_w, Organism::Species::Grass, fhl::ResMgr::loadTexture("grassTex", "res/grass.png"), 0u, _gener) {}
};

#endif