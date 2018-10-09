#ifndef VARIANT_UTILITIES_HPP
#define VARIANT_UTILITIES_HPP


#include <type_traits>
#include <cstddef>


namespace rtw::detail
{
    static constexpr const size_t variant_npos = ~size_t{0};
}


template<typename... Ts>
struct first;

template<typename T, typename... Ts>
struct first<T, Ts...>
{
    using type = T;
};

template<typename... Ts>
using first_t = typename first<Ts...>::type;


template<size_t I, typename T, typename... Ts>
struct get_type {
    static_assert(I <= sizeof...(Ts));
    using type = typename get_type<I-1, Ts...>::type;
};

template<typename T, typename... Ts>
struct get_type<0, T, Ts...>
{
    using type = T;
};

template<size_t I, typename... Ts>
using get_type_t = typename get_type<I, Ts...>::type;


template<template<typename> typename Cond, typename... Ts>
using all_of = std::bool_constant<(Cond<Ts>::value && ...)>;




#endif // VARIANT_UTILITIES_HPP