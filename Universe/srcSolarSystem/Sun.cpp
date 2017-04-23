#include "Sun.h"

Sun::Sun(fhl::ModelData & _md) : Orbitable(_md, nullptr)
{
	setScale(fhl::Vec3f::one() * 0.5f);
	m_model.setUseColorOnly(true);
	m_model.setColor(fhl::Vec3f(255.f, 255.f, 153.f) / 255.f);
}

void Sun::update(float _dt)
{
	for (auto & e : m_satellites)
		e.second->setLight(fhl::Light::point(getPosition(), m_model.getColor(), 100.f, 0.001f, 0.0005f));
	Orbitable::update(nullptr, _dt);
}
