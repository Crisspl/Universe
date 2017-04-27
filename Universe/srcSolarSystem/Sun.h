#ifndef SUN_H
#define SUN_H

#include "Orbitable.h"

class Sun : public Orbitable
{
public:
	Sun(fhl::ModelData & _md, float _rSpeed = -10.f, fhl::Vec3f _rAxis = fhl::Vec3f::up());

	void update(float _dt);
};

#endif