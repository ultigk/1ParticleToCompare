#include "util.h"
#include <cmath>



namespace utils
{
    float ComputeLength(const sf::Vector2f vector)
    {
        return sqrt(vector.x * vector.x + vector.y * vector.y);
    }
}