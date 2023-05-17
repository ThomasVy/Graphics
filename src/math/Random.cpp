#include "Random.h"
#include <random>
std::random_device rd;
namespace math::integer
{
    int Random(int min, int max)
    {
        
        int diff = max - min + 1;
        int num = rd()%diff;
        num += min; 
        return num;                                         
    }
}