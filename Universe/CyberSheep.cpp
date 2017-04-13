#include "CyberSheep.h"

#include "World.h"

std::vector<std::unique_ptr<Organism>>::iterator CyberSheep::findTarget()
{
	using Iter = std::vector<std::unique_ptr<Organism>>::iterator;

	std::vector<Iter> borches;
	auto & organisms = Organism::m_world.getOrganisms();

	auto i = organisms.begin(), end = organisms.end();
	while (i != end)
	{
		i = std::find_if(i, end, [](const std::unique_ptr<Organism> & _o) { return _o->getSpecies() == Organism::Species::SosnowskiBorsch; });
		if (i != end)
			borches.push_back(i++);
	}

	if (borches.empty())
		return Animal::findTarget();

	return *std::min_element(borches.begin(), borches.end(),
		[this](const Iter & _a, const Iter & _b)
	{
		auto distanceA = (this->getPosition() - _a->get()->getPosition()).length();
		auto distanceB = (this->getPosition() - _b->get()->getPosition()).length();
		return distanceA < distanceB;
	});
}
