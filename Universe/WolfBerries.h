#ifndef WOLFBERRIES_H
#define WOLFBERRIES_H

#include "Plant.h"

#include <FHL/Graphics/ResMgr.h>

class WolfBerries :
	public Plant
{
public:
	WolfBerries(World & _w, std::size_t _gener) :
		Plant(_w, Organism::Species::WolfBerries, fhl::ResMgr::loadTexture("wolfBerriesTex", "res/wolfBerries.jpg"), 99u, _gener) {}
};

#endif

