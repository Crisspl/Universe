#ifndef ORBITTOUR_H
#define ORBITTOUR_H

#include <FHL/Maths/vectors.h>

class OrbitTour
{
public:
	virtual ~OrbitTour() = default;

	virtual fhl::Vec3f operator()(float _time) = 0;
};

#endif