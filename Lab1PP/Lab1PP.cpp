#include <Windows.h>

#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Integrand.hpp"
#include "Sequential.hpp"
#include "PosixIntegration.hpp"
#include "STDIntegration.hpp"
#include "Benchmark.hpp"
#include "Accuracy.hpp"

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "Лабораторная работа №1\n";
    std::cout << "Численное интегрирование\n\n";
    std::cout << "Метод: правых прямоугольников\n";
    std::cout << "Функция: (1+x)^2/(x^3 * sqrt(2+x))\n";
    std::cout << "Интервал: [2; 5]\n\n";

    long long n;
    int selectedThreads;
    int maxThreads;

    std::cout << "Введите количество разбиений: ";
    std::cout.flush();
    std::cin >> n;

    std::cout << "Введите количество потоков: ";
    std::cout.flush();
    std::cin >> selectedThreads;

    std::cout << "Введите максимальное количество потоков: ";
    std::cout.flush();
    std::cin >> maxThreads;

    if (n <= 0 || selectedThreads <= 0 || maxThreads <= 0)
    {
        std::cout
            << "Ошибка ввода\n";
        return 1;
    }

    selectedThreads = static_cast<int>(std::min<long long>(selectedThreads,n));
    maxThreads = static_cast<int>(std::min<long long>(maxThreads,n));
    std::cout << "\n";

    CalculationResult single = measureTime([&](){
                return integrateSingleThread(n);
            }
        );

    std::cout << "Однопоточный расчет\n";
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "Результат: " << single.value << "\n";

    std::cout << "Время: " << single.time << " с\n";

    CalculationResult posix = measureTime([&](){
                return integratePThread(n, selectedThreads);
            }
        );

    double posixSpeedup = single.time / posix.time;
    double posixEfficiency = posixSpeedup / selectedThreads * 100.0;

    std::cout << "\nPOSIX\n";
    std::cout << "Потоки: " << selectedThreads << "\n";
    std::cout << "Результат: " << posix.value << "\n";
    std::cout << "Время: " << posix.time << " с\n";
    std::cout << "Ускорение: " << posixSpeedup << "x\n";
    std::cout << "Эффективность: " << posixEfficiency << "%\n";

    CalculationResult stdResult = measureTime([&](){
                return integrateStdThread(n, selectedThreads);
            }
        );

    double stdSpeedup = single.time / stdResult.time;
    double stdEfficiency = stdSpeedup / selectedThreads * 100.0;

    std::cout << "\nstd::thread\n";
    std::cout << "Потоки: " << selectedThreads << "\n";
    std::cout << "Результат: " << stdResult.value << "\n";
    std::cout << "Время: " << stdResult.time << " с\n";
    std::cout << "Ускорение: " << stdSpeedup << "x\n";
    std::cout << "Эффективность: " << stdEfficiency << "%\n";

    testPThreads(n, maxThreads, single.time);
    testStdThreads(n, maxThreads, single.time);

    std::cout << "\nСравнение результатов\n";
    std::cout << std::setprecision(12);
    std::cout << "Однопоточный: " << single.value << "\n";
    std::cout << "POSIX:        " << posix.value << "\n";
    std::cout << "std::thread:  " << stdResult.value << "\n";

    checkAccuracy();

    return 0;
}