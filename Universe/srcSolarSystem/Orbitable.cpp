#include "Orbitable.h"

#include <exception>
#include <limits>

#include <FHL/Graphics/Renderer.h>

Orbitable::Orbitable(fhl::ModelData & _md, std::unique_ptr<OrbitTour> && _ot) :
	m_model(_md),
	m_orbitTrack(std::move(_ot)),
	m_time{0.f}
{
}

void Orbitable::addSatellite(const std::string & _name, std::unique_ptr<Orbitable> && _s)
{
	if (m_satellites.find(_name) == m_satellites.end())
	{
		m_satellites[_name] = std::move(_s);
		m_satellites[_name]->getModel().setShader(fhl::UsingShader::Light);
	}
}

Orbitable & Orbitable::getSatellite(const std::string & _name)
{
	if (m_satellites.find(_name) == m_satellites.end())
		throw std::runtime_error("No satellite with such name");
	return *m_satellites[_name];
}

void Orbitable::render(const fhl::RenderConf &) const
{
	fhl::RenderConf conf;
	conf += getMatrices();
	conf += getLights();
	fhl::Renderer::render(m_model, conf);
	for (const Container::value_type & e : m_satellites)
		fhl::Renderer::render(*e.second);
}

void Orbitable::update(Orbitable * _parent, float _dt)
{
	if (std::numeric_limits<decltype(m_time)>::max() - m_time < _dt)
		m_time = 0.f;
	m_time += _dt;
	rotate(10.f * _dt, fhl::Vec3f::up());
	if (m_orbitTrack && _parent)
		setPosition(_parent->getPosition() + (*m_orbitTrack)(m_time));
	for (Container::value_type & e : m_satellites)
		e.second->update(this, _dt);
}
