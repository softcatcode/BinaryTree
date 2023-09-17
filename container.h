#ifndef CONTAINER_H_INCLUDED
#define CONTAINER_H_INCLUDED

#include <concepts>
#include "comparable.h"
using namespace std;

template <typename A, typename B>
concept Assignable = requires(A a, B b) {
    a = b;
};

template <typename From, typename To>
concept Convertible = convertible_to<From, To>;

template<typename Cont>
concept Container = requires()
{
    typename Cont::size_type;
    typename Cont::value_type;
    typename Cont::iterator;
    typename Cont::const_iterator;
    Comparable<typename Cont::value_type>;
};

template <typename Cont, typename T>
concept TreeConvertibleContainer =
    Convertible<typename Cont::value_type, T> &&
    Assignable<typename Cont::value_type, T>;

template <typename T>
concept Iterator = requires(T a, T b)
{
    typename T::value_type;
    { ++a } -> same_as<T&>;
    { *a } -> same_as<typename T::value_type const&>;
    {a != b} -> same_as<bool>;
};

#endif // CONTAINER_H_INCLUDED
