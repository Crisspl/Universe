#ifndef CYBERSHEEP_H
#define CYBERSHEEP_H

#include "Animal.h"

#include <FHL/Graphics/ResMgr.h>

class CyberSheep :
	public Animal
{
public:
	CyberSheep(World & _world) :
		Animal(_world, Organism::Species::CyberSheep, fhl::ResMgr::loadTexture("cyberSheepTex", "res/cyberSheep.png"), 11u, 4u) {}

	std::vector<std::unique_ptr<Organism>>::iterator findTarget() override;
};

#endif



