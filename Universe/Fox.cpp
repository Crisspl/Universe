#include "Fox.h"

#include "World.h"

std::vector<std::unique_ptr<Organism>>::iterator Fox::findTarget()
{
	using Iter = std::vector<std::unique_ptr<Organism>>::iterator;

	std::vector<Iter> weakerOnes;

	auto i = m_world.getSignificantOrganismsRange().first, end = m_world.getSignificantOrganismsRange().second;
	while (i != end)
	{
		i = std::find_if(i, end, 
			[this](const std::unique_ptr<Organism> & _arg) { return _arg->getStrength() <= this->getStrength() && _arg->getId() != this->getId(); });
		if (i != end)
			weakerOnes.push_back(i++);
	}
	if (weakerOnes.empty())
		return m_world.getOrganisms().end();

	return *std::min_element(weakerOnes.begin(), weakerOnes.end(),
		[this](const Iter & _a, const Iter & _b)
		{
			auto distanceA = (this->getPosition() - _a->get()->getPosition()).length();
			auto distanceB = (this->getPosition() - _b->get()->getPosition()).length();
			return distanceA < distanceB;
		}
	);
}
