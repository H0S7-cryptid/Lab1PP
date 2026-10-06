#include "STDIntegration.hpp"
#include "Integrand.hpp"

#include <vector>
#include <thread>
#include <functional>

void stdThreadWorker(
    long long start,
    long long end,
    long long n,
    double& partialSum)
{
    double h = (B - A) / n;
    double sum = 0.0;

    for (long long i = start;
        i <= end;
        ++i)
    {
        double x = A + i * h;
        sum += function(x);
    }

    partialSum = sum;
}

double integrateStdThread(
    long long n,
    int threadCount)
{
    std::vector<std::thread> threads;
    std::vector<double> partialSums(
        threadCount,
        0.0
    );

    long long base = n / threadCount;
    long long remainder = n % threadCount;
    long long start = 1;

    for (int i = 0; i < threadCount; ++i)
    {
        long long size = base;

        if (i < remainder)
        {
            ++size;
        }

        long long end = start + size - 1;

        threads.emplace_back(
            stdThreadWorker,
            start,
            end,
            n,
            std::ref(partialSums[i])
        );

        start += size;
    }

    for (auto& t : threads)
    {
        t.join();
    }

    double totalSum = 0.0;

    for (double sum : partialSums)
    {
        totalSum += sum;
    }

    double h = (B - A) / n;

    return totalSum * h;
}