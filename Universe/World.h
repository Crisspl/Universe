#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>

#include <FHL/Graphics/Renderable.h>

#include "Organism.h"

class World : public fhl::Renderable
{
	using Container = std::vector<std::unique_ptr<Organism>>;

public:
	World();

	void render(const fhl::RenderConf &) const override;

	void update(float _dt);
	void addOrganism(std::unique_ptr<Organism> && _org);

	Container & getOrganisms() { return m_organisms; }

private:
	Container m_organisms;
};

#endif