#ifndef ORGANISM_H
#define ORGANISM_H

#include <FHL/Graphics/Sprite.h>

class World;

class Organism : public fhl::Transformable, public fhl::Renderable
{
public:
	enum class Species : unsigned
	{
		// animals:
		Antelope,
		CyberSheep,
		Fox,
		Sheep,
		Turtle,
		Wolf,
		// plants:
		Grass,
		Guarna,
		SosnowskiBorsch,
		Sowthistle,
		WolfBerries,

		Count
	};

public:
	Organism(World & _world, Species _species, fhl::Texture & _tex, unsigned _str, unsigned _initiative, std::size_t _gener);
	virtual ~Organism() = default;

	void render(const fhl::RenderConf &) const override;

	Species getSpecies() const { return m_species; }
	unsigned getStrength() const { return m_strength; }
	unsigned getInitiative() const { return m_initiative; }
	std::size_t getId() const { return m_id; }
	std::size_t getGeneration() const { return m_generation; }
	bool isDead() const { return m_dead; }
	bool isAbleToMultiply() const { return m_multiplyTime >= s_multiplyInterval; }

	virtual void update(float _dt) = 0;
	bool isCollision(const Organism & _other) const;
	virtual void contact(Organism & _other);
	void setDead(bool _d) { m_dead = _d; }
	void setAbleToMultiply(bool _a) { m_multiplyTime = _a ? m_multiplyTime : 0.f; }

protected:
	void attack(Organism & _other);
	void addMultiplyTime(float _t) { m_multiplyTime += _t; }
	virtual void takeAttack(Organism & _other);

protected:
	World & m_world;
	unsigned m_strength, m_initiative;

private:
	const Species m_species;
	fhl::Sprite m_sprite;
	const std::size_t m_id, m_generation;
	float m_multiplyTime;
	bool m_dead;

	static std::size_t s_createdCount;
	constexpr static const float s_multiplyInterval = 5.f;
};

#endif

