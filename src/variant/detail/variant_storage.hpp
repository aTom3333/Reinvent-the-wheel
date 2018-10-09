#ifndef VARIANT_STORAGE_HPP
#define VARIANT_STORAGE_HPP


#include <type_traits>
#include <cstddef>
#include <utility>
#include "variant_utilities.hpp"


namespace rtw::detail
{
    
    template<bool trivially_destructible, size_t Index, typename... Ts>
    union variant_underlying_storage;
    
    template<size_t Index, typename... Ts>
    using variant_storage = variant_underlying_storage<
        (std::is_trivially_destructible_v<Ts> && ...), 
        Index,
        Ts...
    >;
    
    template<bool trivially_destructible, size_t Index>
    union variant_underlying_storage<trivially_destructible, Index>
    {
        // End of recursion
        constexpr void destroy([[maybe_unused]] size_t i)
        {}
        
        constexpr void copy([[maybe_unused]] const variant_underlying_storage& other, [[maybe_unused]] size_t i) 
        {}
        
        constexpr void move(variant_underlying_storage&&, size_t)
        {}
    };
    
    
    struct copy_constructor_tag {};


    #define COMMON_VARIANT_UNDERLYING_STORAGE                                   \
    variant_underlying_storage() {}                                             \
                                                                                \
    template<size_t I, typename... Args>                                        \
    constexpr variant_underlying_storage(std::in_place_index_t<I>, Args&&... args)           \
        noexcept(std::is_nothrow_constructible_v<get_type_t<I, T, Ts...>, Args...>)\
        : rest{std::in_place_index_t<I-1>{}, std::forward<Args>(args)...} {}      \
                                                                                \
    template<typename... Args>                                                  \
    constexpr variant_underlying_storage(std::in_place_index_t<0>, Args&&... args)           \
        noexcept(std::is_nothrow_constructible_v<get_type_t<0, T, Ts...>, Args...>)\
        : first{std::forward<Args>(args)...} {}                                 \
                                                                                \
    void copy(const variant_underlying_storage& other, size_t i)                \
    {                                                                           \
        if(i == Index)                                                          \
            ::new (&first) T{other.first};                                      \
        else                                                                    \
            rest.copy(other.rest, i);                                           \
    }                                                                           \
                                                                                \
    void move(variant_underlying_storage&& other, size_t i)                     \
    {                                                                           \
        if(i == Index)                                                          \
            ::new (&first) T{std::move(other.first)};                           \
        else                                                                    \
            rest.move(std::move(other.rest), i);                                \
    }                                                                           \

        
        
    template<size_t Index, typename T, typename...Ts>
    union variant_underlying_storage<true, Index, T, Ts...>
    {
        COMMON_VARIANT_UNDERLYING_STORAGE
        
        T first;
        variant_storage<Index+1, Ts...> rest;
    };

    template<size_t Index, typename T, typename...Ts>
    union variant_underlying_storage<false, Index, T, Ts...>
    {
        // Not trivially destructible
        ~variant_underlying_storage() noexcept((std::is_nothrow_destructible_v<T> && ... && std::is_nothrow_destructible_v<Ts>))
        {}

        constexpr void destroy(size_t i)
        {
            if(i == Index)
                first.~T();
            else
                rest.destroy(i);
        }
        
        COMMON_VARIANT_UNDERLYING_STORAGE
        
        T first;
        variant_storage<Index+1, Ts...> rest;
    };

    #undef COMMON_VARIANT_UNDERLYING_STORAGE
}

#endif // VARIANT_STORAGE_HPP