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

#pragma comment(lib, "pthreadVC2.lib")

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "Лабораторная работа №1\n";
    std::cout << "Численное интегрирование\n\n";

    std::cout << "Метод: правых прямоугольников\n";
    std::cout << "Функция: (1+x)^2 / "
        "(x^3 * sqrt(2+x))\n";
    std::cout << "Интервал: [2; 5]\n\n";

    long long n;
    int selectedThreads;
    int maxThreads;

    std::cout << "Введите количество разбиений: ";
    std::cin >> n;

    std::cout << "Введите количество потоков: ";
    std::cin >> selectedThreads;

    std::cout << "Введите максимальное количество потоков: ";
    std::cin >> maxThreads;

    if (n <= 0 ||
        selectedThreads <= 0 ||
        maxThreads <= 0)
    {
        std::cout << "Ошибка ввода\n";
        return 1;
    }

    selectedThreads =
        std::min<long long>(selectedThreads, n);

    maxThreads =
        std::min<long long>(maxThreads, n);

    CalculationResult single =
        measureTime([&]()
            {
                return integrateSingleThread(n);
            });

    // дальнейшая часть main практически
    // остаётся такой же, как сейчас
}