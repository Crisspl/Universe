#ifndef GUARANA_H
#define GUARANA_H

#include "Plant.h"

#include <FHL/Graphics/ResMgr.h>

class Guarana :
	public Plant
{
public:
	Guarana(World & _w, std::size_t _gener) :
		Plant(_w, Organism::Species::Guarana, fhl::ResMgr::loadTexture("guaranaTex", "res/guarana.jpg"), 0u, _gener) {}

	void takeAttack(Organism & _other) override;
};

#endif

