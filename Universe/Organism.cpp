#include "Organism.h"

#include <FHL/Graphics/Renderer.h>

std::size_t Organism::s_createdCount = 0u;

Organism::Organism(World & _world, Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative) :
	m_world(_world),
	m_strength(_str),
	m_initiative(_initiative),
	m_species(_species),
	m_sprite(_tex),
	m_id(s_createdCount++)
{
}

void Organism::render(const fhl::RenderConf &) const
{
	fhl::RenderConf conf;
	conf += getMatrices();
	fhl::Renderer::render(m_sprite, conf);
}
