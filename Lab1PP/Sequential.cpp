#include "Sequential.hpp"
#include "Integrand.hpp"

double integrateSingleThread(long long n)
{
    double h = (B - A) / n;
    double sum = 0.0;

    for (long long i = 1; i <= n; ++i)
    {
        double x = A + i * h;
        sum += function(x);
    }

    return sum * h;
}