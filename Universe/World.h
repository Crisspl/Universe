#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <array>
#include <memory>

#include <FHL/Graphics/Renderable.h>
#include <FHL/Maths/Vec2.h>

#include "Organism.h"
#include "Human.h"
#include "Utilities.h"

class World : public fhl::Renderable
{
	using Container = std::vector<std::unique_ptr<Organism>>;
	using Range = std::pair<Container::iterator, Container::iterator>;

public:
	explicit World(fhl::Vec2u _size);

	void render(const fhl::RenderConf &) const override;
	void moveHuman(fhl::Vec2f _dir, float _dt);
	void activateHumanSuperpower() { getHuman().activateExtraStrength(); }
	void update(float _dt);

	void addOrganism(Organism::Species _species, std::size_t _gener);
	void addRandomOrganism(std::size_t _gener);

	Container & getOrganisms() { return m_organisms; }
	Range getSignificantOrganismsRange();
	const fhl::Vec2u & getSize() const { return m_size; }

	void reset();

private:
	void removeDeadOrganisms();
	Human & getHuman() { return reinterpret_cast<Human &>(**m_organisms.begin()); }

private:
	Container m_organisms;
	fhl::Vec2u m_size;
	fhl::Rect m_worldRect;
};

#endif

