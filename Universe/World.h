#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <array>
#include <memory>

#include <FHL/Graphics/Renderable.h>
#include <FHL/Maths/Vec2.h>

#include "Organism.h"
#include "Utilities.h"

class World : public fhl::Renderable
{
	using Container = std::vector<std::unique_ptr<Organism>>;

public:
	explicit World(fhl::Vec2u _size);

	void render(const fhl::RenderConf &) const override;
	void update(float _dt);

	void addOrganism(Organism::Species _species, std::size_t _gener);
	void addRandomOrganism(std::size_t _gener);

	Container & getOrganisms() { return m_organisms; }
	const fhl::Vec2u & getSize() const { return m_size; }

private:
	void removeDeadOrganisms();

private:
	Container m_organisms;
	fhl::Vec2u m_size;
};

#endif

