#include "Utilities.h"

#include <ctime>

std::mt19937 Utilities::m_gen(std::time(nullptr));