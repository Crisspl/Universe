#include "Turtle.h"

void Turtle::takeAttack(Organism & _other)
{
	if (_other.getStrength() < 5)
	{
		fhl::Vec2f dir = (_other.getPosition() - getPosition()).normalized();
		_other.move(dir * 50.f);
		return;
	}
	Organism::takeAttack(_other);
}
