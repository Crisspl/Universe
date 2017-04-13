#ifndef ORGANISM_H
#define ORGANISM_H

#include <FHL/Graphics/Sprite.h>

class World;

class Organism : public fhl::Transformable, public fhl::Renderable
{
protected:
	enum class Species
	{
		Wolf,
		Sheep,
		Fox,
		Turtle,
		Antelope,
		CyberSheep,
		Grass,
		Milkweed,
		Guarna,
		WolfBerries,
		SosnowskiBorsch
	};

public:
	Organism(World & _world, Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative);
	virtual ~Organism() = default;

	void render(const fhl::RenderConf &) const override;

	Species getSpecies() const { return m_species; }
	unsigned getStrength() const { return m_strength; }
	unsigned getInitiative() const { return m_initiative; }
	std::size_t getId() const { return m_id; }

	virtual void update(float _dt) = 0;

protected:
	World & m_world;
	unsigned m_strength, m_initiative;

private:
	const Species m_species;
	fhl::Sprite m_sprite;
	const std::size_t m_id;

	static std::size_t s_createdCount;
};

#endif

