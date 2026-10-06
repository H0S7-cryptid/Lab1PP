#pragma once

#include <chrono>

struct CalculationResult
{
    double value;
    double time;
};

template <typename Function>
CalculationResult measureTime(Function func)
{
    auto start = std::chrono::steady_clock::now();

    double result = func();

    auto finish = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed =
        finish - start;

    return { result, elapsed.count() };
}

void testPThreads(
    long long n,
    int maxThreads,
    double singleTime);

void testStdThreads(
    long long n,
    int maxThreads,
    double singleTime);