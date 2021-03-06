#ifndef SOWTHISTLE_H
#define SOWTHISTLE_H

#include "Plant.h"

#include <FHL/Graphics/ResMgr.h>

class Sowthistle :
	public Plant
{
public:
	Sowthistle(World & _w, std::size_t _gener) :
		Plant(_w, Organism::Species::Sowthistle, fhl::ResMgr::loadTexture("sowthistleTex", "res/sowthistle.jpg"), 0u, _gener) {}
	float getMultiplyInterval() const override { return Organism::getMultiplyInterval() / 3.f; }
	unsigned getMultiplyPercentageChance() const override { return 20u; }
};

#endif

