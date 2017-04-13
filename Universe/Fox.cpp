#include "Fox.h"

#include "World.h"

std::vector<std::unique_ptr<Organism>>::iterator Fox::findTarget()
{
	using Iter = std::vector<std::unique_ptr<Organism>>::iterator;

	std::vector<Iter> weakerOnes;
	auto & organisms = Organism::m_world.getOrganisms();

	auto i = organisms.begin(), end = organisms.end();
	while (i != end)
	{
		i = std::find_if(i, end, [this](const std::unique_ptr<Organism> & _arg) { return _arg->getStrength() < this->getStrength(); });
		if (i != end)
			weakerOnes.push_back(i++);
	}

	return *std::min_element(weakerOnes.begin(), weakerOnes.end(),
		[this](const Iter & _a, const Iter & _b)
	{
		auto distanceA = (this->getPosition() - _a->get()->getPosition()).length();
		auto distanceB = (this->getPosition() - _b->get()->getPosition()).length();
		return distanceA < distanceB;
	});
}