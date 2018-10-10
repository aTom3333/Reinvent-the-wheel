#ifndef VARIANT_DATA_HPP
#define VARIANT_DATA_HPP


#include <type_traits>
#include "variant_utilities.hpp"
#include "variant_storage.hpp"


namespace rtw::detail
{
    // Wrap the union in a struct and add destructor
    template<bool trivially_destructible, typename... Ts>
    struct variant_underlying_data;

    template<typename... Ts>
    using variant_data = variant_underlying_data<
        (std::is_trivially_destructible_v<Ts> && ...),
        Ts...
    >;

    template<typename... Ts>
    struct variant_underlying_data<true, Ts...>
    {
        constexpr variant_underlying_data() {};
        
        template<size_t I, typename... Args>
        constexpr variant_underlying_data(std::in_place_index_t<I> index, Args&&... args)
        noexcept(std::is_nothrow_constructible_v<get_type_t<I, Ts...>, Args...>) :
        storage{index, std::forward<Args>(args)...}, index(I) {}

        //variant_underlying_data(const variant_underlying_data& other) :
        //    storage{other.storage}, index{other.index} {}

        variant_storage<0, Ts...> storage;
        size_t index;
    };

    template<typename... Ts>
    struct variant_underlying_data<false, Ts...> : variant_underlying_data<true, Ts...>
    {
        using base = variant_underlying_data<true, Ts...>;
        
        using base::base;
        
        ~variant_underlying_data() noexcept((std::is_nothrow_destructible_v<Ts> && ...))
        {
            variant_underlying_data<true, Ts...>::storage.destroy(variant_underlying_data<true, Ts...>::index);
        }
    };
    
    // Add copy constructor to the data
    template<bool trivially_copy_constructible, typename... Ts>
    struct copy_constructible_variant_underlying_data;
    
    template<typename... Ts>
    using copy_constructible_variant_data = copy_constructible_variant_underlying_data<
        (std::is_trivially_copy_constructible_v<Ts> && ...),
        Ts...
    >;


    template<typename... Ts>
    struct copy_constructible_variant_underlying_data<true, Ts...> : variant_data<Ts...>
    {
        using base = variant_data<Ts...>;

        using base::base;

        constexpr copy_constructible_variant_underlying_data(const copy_constructible_variant_underlying_data& other)
            noexcept = default;
        constexpr copy_constructible_variant_underlying_data(copy_constructible_variant_underlying_data&&) noexcept = default;
        constexpr copy_constructible_variant_underlying_data& operator=(const copy_constructible_variant_underlying_data&) = default;
        constexpr copy_constructible_variant_underlying_data& operator=(copy_constructible_variant_underlying_data&&) = default;
    };

    template<typename... Ts>
    struct copy_constructible_variant_underlying_data<false, Ts...> : variant_data<Ts...>
    {
        using base = variant_data<Ts...>;

        using base::base;

        constexpr copy_constructible_variant_underlying_data(const copy_constructible_variant_underlying_data& other)
            noexcept((std::is_nothrow_copy_constructible_v<Ts> && ...))
        {
            base::index = variant_npos;
            base::storage.copy(other.storage, other.index);
            base::index = other.index;
        }

        constexpr copy_constructible_variant_underlying_data(copy_constructible_variant_underlying_data&&) noexcept = default;
        constexpr copy_constructible_variant_underlying_data& operator=(const copy_constructible_variant_underlying_data&) = default;
        constexpr copy_constructible_variant_underlying_data& operator=(copy_constructible_variant_underlying_data&&) = default;
    };
    
    
    // Add move constructor
    template<bool trivially_move_constructible, typename... Ts>
    struct move_constructible_variant_underlying_data;
    
    
    template<typename... Ts>
    using move_constructible_variant_data = move_constructible_variant_underlying_data<
        (std::is_trivially_move_constructible_v<Ts> && ...),
        Ts...
    >;

    template<typename... Ts>
    struct move_constructible_variant_underlying_data<true, Ts...> : copy_constructible_variant_data<Ts...>
    {
        using base = copy_constructible_variant_data<Ts...>;

        using base::base;
        
        // TODO noexcept
        constexpr move_constructible_variant_underlying_data(const move_constructible_variant_underlying_data&) = default;
        constexpr move_constructible_variant_underlying_data(move_constructible_variant_underlying_data&&) = default;
        constexpr move_constructible_variant_underlying_data& operator=(const move_constructible_variant_underlying_data&) = default;
        constexpr move_constructible_variant_underlying_data& operator=(move_constructible_variant_underlying_data&&) noexcept = default;
    };

    template<typename... Ts>
    struct move_constructible_variant_underlying_data<false, Ts...> : copy_constructible_variant_data<Ts...>
    {
        using base = copy_constructible_variant_data<Ts...>;
        
        using base::base;
        
        constexpr move_constructible_variant_underlying_data(const move_constructible_variant_underlying_data&) = default;

        constexpr move_constructible_variant_underlying_data(move_constructible_variant_underlying_data&& other)
            noexcept((std::is_nothrow_move_constructible_v<Ts> && ...))
        {
            base::index = variant_npos;
            base::storage.move(std::move(other.storage), other.index);
            base::index = other.index;
        }

        constexpr move_constructible_variant_underlying_data& operator=(const move_constructible_variant_underlying_data&) = default;
        constexpr move_constructible_variant_underlying_data& operator=(move_constructible_variant_underlying_data&&) noexcept = default;
    };
    
    
    // Add copy-assignment
    template<bool trivially_copy_assignable, typename... Ts>
    struct copy_assignable_variant_underlying_data;
    
    template<typename... Ts>
    using copy_assignable_variant_data = copy_assignable_variant_underlying_data<
        (std::is_trivially_copy_assignable_v<Ts> && ...),
        Ts...
    >;
    
    template<typename... Ts>
    struct copy_assignable_variant_underlying_data<true, Ts...> : move_constructible_variant_data<Ts...>
    {
        using base = move_constructible_variant_data<Ts...>;
        
        using base::base;

        //static_assert((std::is_trivial_v<Ts> && ...), "coucou");

        // TODO noexcept
        copy_assignable_variant_underlying_data(const copy_assignable_variant_underlying_data&) = default;
        copy_assignable_variant_underlying_data(copy_assignable_variant_underlying_data&&) = default;
        copy_assignable_variant_underlying_data& operator=(const copy_assignable_variant_underlying_data&) = default;
        copy_assignable_variant_underlying_data& operator=(copy_assignable_variant_underlying_data&&) = default;
    };

    template<typename... Ts>
    struct copy_assignable_variant_underlying_data<false, Ts...> : move_constructible_variant_data<Ts...>
    {
        using base = move_constructible_variant_data<Ts...>;

        using base::base;

        // TODO noexcept
        copy_assignable_variant_underlying_data(const copy_assignable_variant_underlying_data&) = default;
        copy_assignable_variant_underlying_data(copy_assignable_variant_underlying_data&&) = default;

        copy_assignable_variant_underlying_data& operator=(const copy_assignable_variant_underlying_data& other)
            noexcept((std::is_nothrow_copy_assignable_v<Ts> && ...))
        {
            base::storage.destroy(base::index);
            base::index = variant_npos;
            base::storage.copy(other.storage, other.index);
            base::index = other.index;
            
            return *this;
        }

        copy_assignable_variant_underlying_data& operator=(copy_assignable_variant_underlying_data&&) = default;
    };
    
    
    // Add move-assignment
    template<bool trivially_move_assignable, typename... Ts>
    struct move_assignable_variant_underlying_data;
    
    template<typename... Ts>
    using move_assignable_variant_data = move_assignable_variant_underlying_data<
        (std::is_trivially_move_assignable_v<Ts> && ...),
        Ts...
    >;
    
    template<typename... Ts>
    struct move_assignable_variant_underlying_data<true, Ts...> : copy_assignable_variant_data<Ts...>
    {
        using base = copy_assignable_variant_data<Ts...>;
        
        // TODO noexcept
        move_assignable_variant_underlying_data(const move_assignable_variant_underlying_data&) = default;
        move_assignable_variant_underlying_data(move_assignable_variant_underlying_data&&) = default;
        move_assignable_variant_underlying_data& operator=(const move_assignable_variant_underlying_data&) = default;
        move_assignable_variant_underlying_data& operator=(move_assignable_variant_underlying_data&&) noexcept = default;
    };

    template<typename... Ts>
    struct move_assignable_variant_underlying_data<false, Ts...> : copy_assignable_variant_data<Ts...>
    {
        using base = copy_assignable_variant_data<Ts...>;
        
        // TODO noexcept
        move_assignable_variant_underlying_data(const move_assignable_variant_underlying_data&) = default;
        move_assignable_variant_underlying_data(move_assignable_variant_underlying_data&&) = default;
        move_assignable_variant_underlying_data& operator=(const move_assignable_variant_underlying_data&) = default;
        
        move_assignable_variant_underlying_data& operator=(move_assignable_variant_underlying_data&& other)
            noexcept((std::is_nothrow_move_assignable_v<Ts> && ...))
        {
            base::storage.destroy(base::index);
            base::index = variant_npos;
            base::storage.move(std::move(other.storage), other.index);
            base::index = other.index;
            
            return *this;
        }
    };
}

#endif // VARIANT_DATA_HPP