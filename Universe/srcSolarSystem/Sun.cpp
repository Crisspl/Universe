#include "Sun.h"

Sun::Sun(fhl::ModelData & _md, float _rSpeed, fhl::Vec3f _rAxis) : Orbitable(_md, nullptr, _rSpeed, _rAxis)
{
	setScale(fhl::Vec3f::one() * 0.5f);
}

void Sun::update(float _dt)
{
	for (auto & e : m_satellites)
		e.second->setLight(fhl::Light::point(getPosition(), fhl::Color::White, 100.f, 0.001f, 0.0005f));

	Orbitable::update(nullptr, _dt);
}
