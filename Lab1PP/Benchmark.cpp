#include "Benchmark.hpp"
#include "PosixIntegration.hpp"
#include "STDIntegration.hpp"

#include <iostream>
#include <iomanip>

void printHeader()
{
    std::cout << std::left
        << "Потоки"
        << "\tВремя"
        << "\t      Результат"
        << "\t      Ускорение"
        << "\t      Эффективность"
        << "\n";
}

void printRow(
    int threads,
    double time,
    double result,
    double speedup)
{
    double efficiency = speedup / threads * 100.0;

    std::cout << std::left
        << std::setw(8)
        << threads

        << std::setw(14)
        << std::fixed
        << std::setprecision(6)
        << time

        << std::setw(18)
        << std::fixed
        << std::setprecision(6)
        << result

        << std::setw(14)
        << std::fixed
        << std::setprecision(4)
        << speedup

        << std::setw(16)
        << std::fixed
        << std::setprecision(2)
        << efficiency
        << "%\n";
}

void testPThreads(
    long long n,
    int maxThreads,
    double singleTime)
{
    std::cout << "\nPOSIX threads\n";
    printHeader();

    for (int threads = 1;
        threads <= maxThreads;
        ++threads)
    {
        CalculationResult r =
            measureTime([&]()
                {
                    return integratePThread(n, threads);
                });

        double speedup = singleTime / r.time;

        printRow(
            threads,
            r.time,
            r.value,
            speedup
        );
    }
}

void testStdThreads(
    long long n,
    int maxThreads,
    double singleTime)
{
    std::cout << "\nstd::thread\n";
    printHeader();

    for (int threads = 1;
        threads <= maxThreads;
        ++threads)
    {
        CalculationResult r =
            measureTime([&]()
                {
                    return integrateStdThread(n, threads);
                });

        double speedup = singleTime / r.time;

        printRow(
            threads,
            r.time,
            r.value,
            speedup
        );
    }
}