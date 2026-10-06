#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

#include "PosixIntegration.hpp"
#include "Integrand.hpp"

#include <vector>

struct PThreadData
{
    long long start;
    long long end;
    long long n;
    double partialSum;
};

void* pthreadWorker(void* arg)
{
    PThreadData* data =
        static_cast<PThreadData*>(arg);

    double h = (B - A) / data->n;
    double sum = 0.0;

    for (long long i = data->start;
        i <= data->end;
        ++i)
    {
        double x = A + i * h;
        sum += function(x);
    }

    data->partialSum = sum;

    return nullptr;
}

double integratePThread(
    long long n,
    int threadCount)
{
    std::vector<pthread_t> threads(threadCount);
    std::vector<PThreadData> data(threadCount);

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

        data[i].start = start;
        data[i].end = start + size - 1;
        data[i].n = n;
        data[i].partialSum = 0.0;

        pthread_create(
            &threads[i],
            nullptr,
            pthreadWorker,
            &data[i]
        );

        start += size;
    }

    double totalSum = 0.0;

    for (int i = 0; i < threadCount; ++i)
    {
        pthread_join(
            threads[i],
            nullptr
        );

        totalSum += data[i].partialSum;
    }

    double h = (B - A) / n;

    return totalSum * h;
}