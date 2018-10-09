#include "catch.hpp"
#include "variant.hpp"
#include <type_traits>
#include <iostream>


TEST_CASE("Triviality inheritance")
{
    SECTION("Built-in types")
    {
        using trivial_variant = rtw::variant<int, float>;

        REQUIRE(std::is_trivially_copy_constructible_v<trivial_variant>);
        REQUIRE(std::is_trivially_move_constructible_v<trivial_variant>);
        REQUIRE(std::is_trivially_copy_assignable_v<trivial_variant>);
        REQUIRE(std::is_trivially_move_assignable_v<trivial_variant>);
        REQUIRE(std::is_trivially_destructible_v<trivial_variant>);
        REQUIRE(std::is_trivially_copyable_v<trivial_variant>);
    }
    
    
    SECTION("Trivially copy-constructible only")
    {
        struct trivial_copy
        {
            trivial_copy(const trivial_copy&) noexcept = default;               // trivial
            trivial_copy(trivial_copy&&) noexcept {}                            // non-trivial
            trivial_copy& operator=(const trivial_copy&) noexcept = default;    // trivial
            trivial_copy& operator=(trivial_copy&&) noexcept { return *this; }  // non-trivial
            ~trivial_copy() noexcept = default;                                 // trivial
        };
        
        SECTION("Test of the test struct")
        {
            REQUIRE(std::is_trivially_copy_constructible_v<trivial_copy>);
            REQUIRE_FALSE(std::is_trivially_move_constructible_v<trivial_copy>);
            REQUIRE(std::is_trivially_copy_assignable_v<trivial_copy>);
            REQUIRE_FALSE(std::is_trivially_move_assignable_v<trivial_copy>);
            REQUIRE(std::is_trivially_destructible_v<trivial_copy>);
        }
        
        using variant = rtw::variant<int, trivial_copy>;
        
        REQUIRE(std::is_trivially_copy_constructible_v<variant>);
        REQUIRE_FALSE(std::is_trivially_move_constructible_v<variant>);
        REQUIRE(std::is_trivially_copy_assignable_v<variant>);
        REQUIRE_FALSE(std::is_trivially_move_assignable_v<variant>);
        REQUIRE(std::is_trivially_destructible_v<variant>);
    }
    
}