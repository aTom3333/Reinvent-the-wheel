#ifndef VARIANT_HPP
#define VARIANT_HPP


#include <type_traits>
#include <cstddef>
#include <utility>
#include "detail/variant_data.hpp"
#include "detail/enable_special_method.hpp"


namespace rtw
{
    static constexpr const size_t variant_npos = detail::variant_npos;
    
    template<typename... Ts>
    class variant : private detail::enable_special_method<Ts...>
    {
        public:
            constexpr variant() noexcept(std::is_nothrow_default_constructible_v<first_t<Ts...>>);
            
            constexpr variant(const variant& other) noexcept((std::is_nothrow_copy_constructible_v<Ts> && ...)) = default;
            constexpr variant(variant&& other) noexcept((std::is_nothrow_move_constructible_v<Ts> && ...)) = default;
            constexpr variant& operator=(const variant&) noexcept((std::is_nothrow_copy_assignable_v<Ts> && ...)) = default;
            constexpr variant& operator=(variant&&) noexcept((std::is_nothrow_move_assignable_v<Ts> && ...)) = default;
            
            template<size_t I, typename... Args>
            constexpr explicit variant(std::in_place_index_t<I>, Args&&... args) noexcept(std::is_nothrow_constructible_v<get_type_t<I, Ts...>, Args...>);
            
            constexpr size_t index() const noexcept;
            
        private:
            using data_t = rtw::detail::move_assignable_variant_data<Ts...>;
            data_t data;
    };
}

#include "detail/variant_impl.hpp"

#endif // VARIANT_HPP