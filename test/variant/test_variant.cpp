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


TEST_CASE("noexcept inheritance")
{
    SECTION("Built-in types")
    {
        using variant = rtw::variant<int, float>;

        REQUIRE(std::is_nothrow_default_constructible_v<variant>);
        REQUIRE(std::is_nothrow_copy_constructible_v<variant>);
        REQUIRE(std::is_nothrow_move_constructible_v<variant>);
        REQUIRE(std::is_nothrow_copy_assignable_v<variant>);
        REQUIRE(std::is_nothrow_move_assignable_v<variant>);
        REQUIRE(std::is_nothrow_destructible_v<variant>);

        REQUIRE(std::is_nothrow_constructible_v<variant, std::in_place_index_t<0>, int>);
        REQUIRE(std::is_nothrow_constructible_v<variant, std::in_place_index_t<1>, float>);
    }
    
    SECTION("String")
    {
        SECTION("Test the test")
        {
            REQUIRE(std::is_nothrow_default_constructible_v<std::string>);
            REQUIRE_FALSE(std::is_nothrow_copy_constructible_v<std::string>);
            REQUIRE(std::is_nothrow_move_constructible_v<std::string>);
            REQUIRE_FALSE(std::is_nothrow_copy_assignable_v<std::string>);
            REQUIRE(std::is_nothrow_move_assignable_v<std::string>);
            REQUIRE(std::is_nothrow_destructible_v<std::string>);
        }
        
        using variant = rtw::variant<int, std::string, float>;
        
        REQUIRE(std::is_nothrow_default_constructible_v<variant>);
        REQUIRE_FALSE(std::is_nothrow_copy_constructible_v<variant>);
        REQUIRE(std::is_nothrow_move_constructible_v<variant>);
        REQUIRE_FALSE(std::is_nothrow_copy_assignable_v<variant>);
        REQUIRE(std::is_nothrow_move_assignable_v<variant>);
        REQUIRE(std::is_nothrow_destructible_v<variant>);

        REQUIRE(std::is_nothrow_constructible_v<variant, std::in_place_index_t<0>, int>);
        REQUIRE_FALSE(std::is_nothrow_constructible_v<variant, std::in_place_index_t<1>, const char*>);
        REQUIRE(std::is_nothrow_constructible_v<variant, std::in_place_index_t<2>, float>);
    }
    
    SECTION("Unusual behaviour")
    {
        struct unusual {
            unusual() noexcept(false) {};
            unusual(const unusual&) noexcept {};
            unusual(unusual&&) noexcept(false) {};
            unusual& operator=(const unusual&) noexcept { return *this; }
            unusual& operator=(unusual&&) noexcept(false) { return *this; }
            ~unusual() noexcept(false) {}
        };
        
        SECTION("Test the test")
        {
            REQUIRE_FALSE(std::is_nothrow_default_constructible_v<unusual>);
            //REQUIRE(std::is_nothrow_copy_constructible_v<unusual>); // Disable test because checks alos if destructor is noexcept
            REQUIRE_FALSE(std::is_nothrow_move_constructible_v<unusual>);
            REQUIRE(std::is_nothrow_copy_assignable_v<unusual>);
            REQUIRE_FALSE(std::is_nothrow_move_assignable_v<unusual>);
            REQUIRE_FALSE(std::is_nothrow_destructible_v<unusual>);
        }
        
        using variant = rtw::variant<unusual>;

        REQUIRE_FALSE(std::is_nothrow_default_constructible_v<variant>);
        //REQUIRE(std::is_nothrow_copy_constructible_v<variant>); // Disable test because checks alos if destructor is noexcept
        REQUIRE_FALSE(std::is_nothrow_move_constructible_v<variant>);
        REQUIRE(std::is_nothrow_copy_assignable_v<variant>);
        REQUIRE_FALSE(std::is_nothrow_move_assignable_v<variant>);
        REQUIRE_FALSE(std::is_nothrow_destructible_v<variant>);
    }
}


TEST_CASE("Constructibility inheritance")
{
    SECTION("Built-in types")
    {
        using variant = rtw::variant<int, float>;
        
        REQUIRE(std::is_default_constructible_v<variant>);
        REQUIRE(std::is_copy_constructible_v<variant>);
        REQUIRE(std::is_move_constructible_v<variant>);
        REQUIRE(std::is_copy_assignable_v<variant>);
        REQUIRE(std::is_move_assignable_v<variant>);
        REQUIRE(std::is_destructible_v<variant>);

        REQUIRE(std::is_constructible_v<variant, std::in_place_index_t<0>, int>);
        REQUIRE(std::is_constructible_v<variant, std::in_place_index_t<1>, float>);
    }
    
    SECTION("Unique pointer")
    {
        SECTION("Test the test")
        {
            REQUIRE(std::is_default_constructible_v<std::unique_ptr<int>>);
            REQUIRE_FALSE(std::is_copy_constructible_v<std::unique_ptr<int>>);
            REQUIRE(std::is_move_constructible_v<std::unique_ptr<int>>);
            REQUIRE_FALSE(std::is_copy_assignable_v<std::unique_ptr<int>>);
            REQUIRE(std::is_move_assignable_v<std::unique_ptr<int>>);
            REQUIRE(std::is_destructible_v<std::unique_ptr<int>>);

            REQUIRE(std::is_constructible_v<std::unique_ptr<int>, int*>);
        }
        
        using variant = rtw::variant<std::unique_ptr<int>>;

        REQUIRE(std::is_default_constructible_v<variant>);
        REQUIRE_FALSE(std::is_copy_constructible_v<variant>);
        REQUIRE(std::is_move_constructible_v<variant>);
        REQUIRE_FALSE(std::is_copy_assignable_v<variant>);
        REQUIRE(std::is_move_assignable_v<variant>);
        REQUIRE(std::is_destructible_v<variant>);

        REQUIRE(std::is_constructible_v<variant, std::in_place_index_t<0>, int*>);
    }
}