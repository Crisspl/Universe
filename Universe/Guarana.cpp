#include "Guarana.h"

void Guarana::takeAttack(Organism & _other)
{
	_other.setStrength(_other.getStrength() + 3u);
	setDead(true);
}
