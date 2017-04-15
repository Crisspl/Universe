#include "OrganismFactory.h"

#include "Antelope.h"
#include "CyberSheep.h"
#include "Fox.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Wolf.h"

std::map<Organism::Species, OrganismFactory::Func_t> OrganismFactory::m_functions{
	std::make_pair(Organism::Species::Antelope, &OrganismFactory::createOrganism<Antelope>),
	std::make_pair(Organism::Species::CyberSheep, &OrganismFactory::createOrganism<CyberSheep>),
	std::make_pair(Organism::Species::Fox, &OrganismFactory::createOrganism<Fox>),
	std::make_pair(Organism::Species::Sheep, &OrganismFactory::createOrganism<Sheep>),
	std::make_pair(Organism::Species::Turtle, &OrganismFactory::createOrganism<Turtle>),
	std::make_pair(Organism::Species::Wolf, &OrganismFactory::createOrganism<Wolf>)
};

