#ifndef ORGANISMFACTORY_H
#define ORGANISMFACTORY_H

#include <memory>
#include <map>
#include <type_traits>

#include "Organism.h"

class OrganismFactory
{
	OrganismFactory() = delete;
	using Func_t = std::unique_ptr<Organism>(*)(World &, std::size_t);

public:
	static std::unique_ptr<Organism> createOrganism(Organism::Species _species, World & _w, std::size_t _gener)
	{
		return m_functions[_species](_w, _gener);
	}

private:
	template<typename T>
	static std::unique_ptr<Organism> createOrganism(World & _w, std::size_t _gener);

private:
	static std::map<Organism::Species, Func_t> m_functions;
};

template<typename T>
std::unique_ptr<Organism> OrganismFactory::createOrganism(World & _w, std::size_t _gener)
{
	static_assert(std::is_base_of<Organism, T>::value, "T is not child class of Organism");
	return std::make_unique<T>(_w, _gener);
}

#endif
