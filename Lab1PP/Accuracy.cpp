#include "Accuracy.hpp"
#include "Sequential.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>

void checkAccuracy()
{
    std::cout << "\nПроверка точности\n";

    const double epsilons[] = { 1e-2, 1e-3 };

    for (double epsilon : epsilons)
    {
        long long n = 1;
        double previous = integrateSingleThread(n);

        while (true)
        {
            n *= 2;

            double current =
                integrateSingleThread(n);

            double error =
                std::fabs(current - previous);

            if (error < epsilon)
            {
                std::cout << std::fixed
                    << std::setprecision(10)
                    << "epsilon = "
                    << epsilon
                    << ", n = "
                    << n
                    << ", I(n) = "
                    << current
                    << ", ошибка = "
                    << error
                    << "\n";

                break;
            }

            previous = current;
        }
    }
}