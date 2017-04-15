#include "Antelope.h"

#include "Utilities.h"

void Antelope::takeAttack(Organism & _other)
{
	if (_other.getStrength() > this->getStrength() && Utilities::random<int>(0, 1))
	{
		fhl::Vec2f dir = (this->getPosition() - _other.getPosition()).normalized();
		move(dir * 50.f);
		return;
	}
	Organism::takeAttack(_other);
}
