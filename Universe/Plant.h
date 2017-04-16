#ifndef PLANT_H
#define PLANT_H

#include "Organism.h"

class Plant :
	public Organism
{
public:
	Plant(World & _world, Organism::Species _species, fhl::Texture & _tex, unsigned _str, std::size_t _gener);
	virtual ~Plant() = default;

	void update(float _dt) override;
	void contact(Organism & _other) override;
	void takeAttack(Organism & _other) override;
	std::unique_ptr<Organism> multiply() const override;
};

#endif

