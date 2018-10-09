#ifndef VARIANT_IMPL_HPP
#define VARIANT_IMPL_HPP


#include "../variant.hpp"

namespace rtw
{
    template<typename... Ts>
    constexpr variant<Ts...>::variant() noexcept(std::is_nothrow_default_constructible_v<first_t<Ts...>>):
        data{std::in_place_index_t<0>{}}
    {
        static_assert(std::is_default_constructible_v<first_t<Ts...>>); // TODO Remplacer l'erreur par une non participation à la résolution d'overload
    }

    template<typename... Ts>
    template<size_t I, typename... Args>
    constexpr variant<Ts...>::variant(std::in_place_index_t<I> index,
                                      Args&& ... args) noexcept(std::is_nothrow_constructible_v<get_type_t<I, Ts...>, Args...>) :
        data{index, std::forward<Args>(args)...}
    {}

    template<typename... Ts>
    constexpr size_t variant<Ts...>::index() const noexcept
    {
        return data.index;
    }
    /*
    template<typename... Ts>
    template<size_t I, typename... Args>
    constexpr variant<Ts...>::variant(std::in_place_index_t<I>, Args&& ... args) noexcept
    {
        size_t test = 0;
        ((test++ == I ? new (&data_) Ts(args...), void() : void()), ...);
        index_ = I;
    }*/
}

#endif // VARIANT_IMPL_HPP