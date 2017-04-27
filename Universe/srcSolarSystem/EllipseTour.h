#ifndef ELLPISETOUR_H
#define ELLPISETOUE_H

#include <cmath>

#include "OrbitTour.h"

class EllipseTour : public OrbitTour
{
public:
	EllipseTour(float _rx, float _rz, float _sp = 1.f) : m_rx{ _rx }, m_rz{ _rz }, m_speed{ _sp } {}

	fhl::Vec3f operator()(float _time) override
	{
		return{ std::cos(_time * m_speed) * m_rx, 0.f , std::sin(_time * m_speed) * m_rz };
	}

private:
	float m_rx, m_rz, m_speed;
};

#endif