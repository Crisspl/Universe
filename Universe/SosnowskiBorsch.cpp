#include "SosnowskiBorsch.h"

void SosnowskiBorsch::takeAttack(Organism & _other)
{
	if (_other.getSpecies() != Organism::Species::CyberSheep)
		_other.setDead(true);
	setDead(true);
}
