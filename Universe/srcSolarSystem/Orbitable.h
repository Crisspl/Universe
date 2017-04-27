#ifndef ORBITABLE_H
#define ORBITABLE_H

#include <memory>
#include <unordered_map>

#include <FHL/Graphics/Transformable3D.h>
#include <FHL/Graphics/Renderable.h>
#include <FHL/Graphics/Model.h>

#include "OrbitTour.h"

class Orbitable : public fhl::Transformable3D, public fhl::Renderable, public fhl::Litable
{
	using Container = std::unordered_map<std::string, std::unique_ptr<Orbitable>>;

public:
	Orbitable(fhl::ModelData & _md, std::unique_ptr<OrbitTour> && _ot, float _rSpeed = 60.f, fhl::Vec3f _rAxis = fhl::Vec3f::up());

	void addSatellite(const std::string & _name, std::unique_ptr<Orbitable> && _s);
	void setOrbitTour(std::unique_ptr<OrbitTour> _ot) { m_orbitTrack = std::move(_ot); }

	void setLight(const fhl::Light & _light) override;

	Orbitable & getSatellite(const std::string & _name);
	fhl::Model & getModel() { return m_model; }

	void render(const fhl::RenderConf &) const override;
	void update(Orbitable * _parent, float _dt);

protected:
	Container m_satellites;
	fhl::Model m_model;
	std::unique_ptr<OrbitTour> m_orbitTrack;
	float m_rotateSpeed;
	fhl::Vec3f m_rotateAxis;
	float m_time;
};

#endif
