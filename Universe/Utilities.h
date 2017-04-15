#ifndef UTILITIES_H
#define UTILITIES_H

#include <random>

#include <FHL/Maths/Vec2.h>

class Utilities
{
	Utilities() = delete;

public:
	template<typename IntType>
	static IntType random(IntType _min, IntType _max)
	{
		return std::uniform_int_distribution<IntType>{ _min, _max }(m_gen);
	}

	static fhl::Vec2i randomVec2i(int _min, int _max)
	{
		return{ random<int>(_min, _max), random<int>(_min, _max) };
	}
	static fhl::Vec2i randomNonZeroVec2i(int _min, int _max)
	{
		fhl::Vec2i ret;
		do
		{
			ret = randomVec2i(_min, _max);
		} while (ret == fhl::Vec2i::zero());
		return ret;
	}

private:
	static std::mt19937 m_gen;
};

#endif