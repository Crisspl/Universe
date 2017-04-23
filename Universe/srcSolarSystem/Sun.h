#ifndef SUN_H
#define SUN_H

#include "Orbitable.h"

class Sun : public Orbitable
{
public:
	Sun(fhl::ModelData & _md);

	void update(float _dt);
};

#endif