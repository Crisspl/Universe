#ifndef ANIMAL_H
#define ANIMAL_H

#include "Organism.h"

class Animal :
	public Organism
{
public:
	Animal(World & _world, Organism::Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative, std::size_t _gener);
	virtual ~Animal() = default;

	virtual void update(float _dt) override;
	void contact(Organism & _other) override;

protected:
	virtual std::vector<std::unique_ptr<Organism>>::iterator findTarget();
	virtual float getVelocity() const { return s_defaultVelocity; }

protected:
	constexpr static const float s_defaultVelocity = 20.f;
};

#endif