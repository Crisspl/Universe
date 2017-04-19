#include "Human.h"

void Human::update(float _dt)
{
	if (m_extraStr.value > 0)
		m_extraStr.time += _dt;
	else
		m_extraStr.cooldownLeft -= _dt;
	if (m_extraStr.time >= 1.f)
	{
		if (--m_extraStr.value == 0u)
		{
			deactivateExtraStength();
		}
		m_extraStr.time = 0.f;
	}
}

void Human::activateExtraStrength()
{
	if (m_extraStr.cooldownLeft <= 0.f)
	{
		m_extraStr.value = ExtraStrength::maxVal;
		m_sprite.setColor(s_extraStrActivatedColor);
	}
}

void Human::deactivateExtraStength()
{
	m_sprite.setColor(fhl::Color::White);
	m_extraStr.cooldownLeft = ExtraStrength::cooldown;
}
