#ifndef COMPARABLE_H
#define COMPARABLE_H

#include <concepts>
using namespace std;

template<typename T>
concept Comparable = requires(T a, T b)
{
    a == b;
    a != b;
    a < b;
    a <= b;
    a > b;
    a >= b;
};

#endif // COMPARABLE_H
