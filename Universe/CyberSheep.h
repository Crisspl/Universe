#ifndef CYBERSHEEP_H
#define CYBERSHEEP_H

#include "Animal.h"

#include <FHL/Graphics/ResMgr.h>

class CyberSheep :
	public Animal
{
public:
	CyberSheep(World & _world, std::size_t _gener) :
		Animal(_world, Organism::Species::CyberSheep, fhl::ResMgr::loadTexture("cyberSheepTex", "res/cyberSheep2.png"), 11u, 4u, _gener) {}

	std::vector<std::unique_ptr<Organism>>::iterator findTarget() override;
};

#endif



