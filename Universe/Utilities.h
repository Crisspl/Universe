#ifndef UTILITIES_H
#define UTILITIES_H

#include <random>

class Utilities
{
	Utilities() = delete;

public:
	template<typename IntType>
	static IntType random(IntType _min, IntType _max)
	{
		return std::uniform_int_distribution<IntType>{ _min, _max }(m_gen);
	}

private:
	static std::mt19937 m_gen;
};

#endif