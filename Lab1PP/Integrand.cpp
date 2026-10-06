#include "Integrand.hpp"

#include <cmath>

const double A = 2.0;
const double B = 5.0;

double function(double x)
{
    return ((1.0 + x) * (1.0 + x)) /
        (x * x * x * sqrt(2.0 + x));
}