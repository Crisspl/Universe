#ifndef HUMAN_H
#define HUMAN_H

#include "Animal.h"

#include <FHL/Graphics/ResMgr.h>

class Human :
	public Animal
{
	struct ExtraStrength
	{
		bool active = false;
		std::size_t value = 0u;
		float time = 0.f, cooldownLeft = 0.f;
		static constexpr std::size_t maxVal = 10u;
		static constexpr float cooldown = 5.f;
	};

public:
	Human(World & _world, std::size_t _gener) :
		Animal(_world, Organism::Species::Human, fhl::ResMgr::loadTexture("humanTex", "res/human.jpg"), 5u, 4u, _gener) {}

	void update(float _dt) override;
	unsigned getStrength() const override { return Organism::getStrength() + m_extraStr.value; }
	void activateExtraStrength();
	
private:
	void deactivateExtraStength();

private:
	ExtraStrength m_extraStr;

	constexpr static fhl::Color s_extraStrActivatedColor = fhl::Color(1.f, 0.f, 0.f);
};

#endif

