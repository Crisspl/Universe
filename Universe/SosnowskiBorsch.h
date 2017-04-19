#ifndef SOSNOWSKIBORCH_H
#define SOSNOWSKIBORCH_H

#include "Plant.h"

#include <FHL/Graphics/ResMgr.h>

class SosnowskiBorsch : // no idea whether i should translate "barszcz sosnowski" :D
	public Plant
{
public:
	SosnowskiBorsch(World & _w, std::size_t _gener) :
		Plant(_w, Organism::Species::SosnowskiBorsch, fhl::ResMgr::loadTexture("sosnowskiBorchTex", "res/sosnowskiBorch.jpg"), 10u, _gener) {}
	void takeAttack(Organism & _other) override;
};

#endif



