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
	using AddFunc_t = void(World::*)(std::size_t);

public:
	explicit World(fhl::Vec2u _size);

	void render(const fhl::RenderConf &) const override;
	void update(float _dt);

	template<typename _T>
	void addOrganism(std::size_t _gener = 0u);
	void addRandomOrganism(std::size_t _gener = 0u);

	Container & getOrganisms() { return m_organisms; }
	const fhl::Vec2u & getSize() const { return m_size; }

private:
	void removeDeadOrganisms();

private:
	Container m_organisms;
	fhl::Vec2u m_size;

	static std::array<AddFunc_t, 6> s_addFunctions;
};

template<typename _T>
void World::addOrganism(std::size_t _gener)
{
	m_organisms.push_back(std::make_unique<_T>(*this, _gener));
	m_organisms.rbegin()->get()->setPosition({
		static_cast<float>(Utilities::random<int>(0, m_size.x)),
		static_cast<float>(Utilities::random<int>(0, m_size.y)) 
	});
}

#endif

