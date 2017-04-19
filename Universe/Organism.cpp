#include "Organism.h"

#include <FHL/Graphics/Renderer.h>

#include "OrganismFactory.h"

std::size_t Organism::s_createdCount = 0u;

Organism::Organism(World & _world, Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative, std::size_t _gener) :
	m_world(_world),
	m_sprite(_tex),
	m_strength(_str),
	m_initiative(_initiative),
	m_species(_species),
	m_id(s_createdCount++),
	m_generation(_gener),
	m_multiplyTime(0.f),
	m_dead(false)
{
}

void Organism::render(const fhl::RenderConf &) const
{
	fhl::RenderConf conf;
	conf += getMatrices();
	fhl::Renderer::render(m_sprite, conf);
}

bool Organism::isCollision(const Organism & _other) const
{
	if (isDead() || _other.isDead())
		return false;
	return fhl::Rect(getPosition(), m_sprite.getSize()).intersects(fhl::Rect(_other.getPosition(), _other.m_sprite.getSize()));
}

void Organism::contact(Organism & _other)
{
	if (getSpecies() == _other.getSpecies())
		return;
	if (_other.isPlant())
		attack(_other);
	if (m_initiative > _other.m_initiative)
		attack(_other);
	else if (m_initiative < _other.m_initiative)
		_other.attack(*this);
	else
	{
		if (m_generation > _other.m_generation)
			attack(_other);
		else
			_other.attack(*this);
	}
}

void Organism::attack(Organism & _other)
{
	_other.takeAttack(*this);
}

void Organism::takeAttack(Organism & _other)
{
	if (_other.getStrength() >= this->getStrength())
		setDead(true);
	else
		_other.setDead(true);
}

std::unique_ptr<Organism> Organism::multiply() const
{
	return OrganismFactory::createOrganism(getSpecies(), m_world, getGeneration() + 1);
}
