#ifndef PLANT_H
#define PLANT_H

#include "Organism.h"

class Plant :
	public Organism
{
public:
	Plant(World & _world, Organism::Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative, std::size_t _gener);
	virtual ~Plant() = default;

	virtual void update(float _dt) override {}
};

#endif

