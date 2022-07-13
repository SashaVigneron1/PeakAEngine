
#include <algorithm>

void Clamp(float& value, float min, float max) 
{
	value = std::min(value, max);
	value = std::max(value, min);
}