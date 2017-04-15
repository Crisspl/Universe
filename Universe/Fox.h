#ifndef FOX_H
#define FOX_H

#include "Animal.h"

#include <FHL/Graphics/ResMgr.h>

class Fox :
	public Animal
{
public:
	Fox(World & _world, std::size_t _gener) :
		Animal(_world, Organism::Species::Fox, fhl::ResMgr::loadTexture("foxTex", "res/fox.png"), 3u, 7u, _gener) {}

	std::vector<std::unique_ptr<Organism>>::iterator findTarget() override;
};

#endif

