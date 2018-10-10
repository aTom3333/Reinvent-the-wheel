#include <iostream>
#include "src/variant/variant.hpp"
#include <variant>


template<int i>
struct watcher
{
    watcher() { std::cout << "watcher<" << i << ">()\n"; }
    watcher(const watcher& other) { std::cout << "watcher<" << i << ">(const watcher&)\n"; }
    watcher(watcher&& other) { std::cout << "watcher<" << i << ">(const watcher&)\n"; }
    ~watcher() { std::cout << "~watcher<" << i << ">()\n"; }
};

template<size_t I>
struct alacon {
    alacon() = delete;
    alacon(int a):x{a} {} 
    
    int x;
};

struct faitchier { // Literal-type but with non-trivial copy-constructor
    constexpr faitchier() : x{0} {}
    constexpr faitchier(int a) : x{a} {}
    constexpr faitchier(const faitchier& other) : x{other.x+1} {}
    
    int x;
};

struct trivial_copy
{
    trivial_copy() = default;
    trivial_copy(const trivial_copy&) noexcept = default;               // trivial
    trivial_copy(trivial_copy&&) noexcept {}                            // non-trivial
    trivial_copy& operator=(const trivial_copy&) noexcept = default;    // trivial
    trivial_copy& operator=(trivial_copy&&) noexcept { return *this; }  // non-trivial
    ~trivial_copy() noexcept = default;                                 // trivial
};

int main()
{
    /*
    rtw::variant<watcher<1>, watcher<2>> v;
    rtw::variant<watcher<3>, watcher<4>> v2{std::in_place_index_t<1>{}};
    
    constexpr rtw::variant<int, float> v3;//{std::in_place_index_t<1>{}};
    rtw::variant<int, float> v5 = v3; // Trivial copy-construct

    union test { alacon<0> blop; alacon<1> plouf; };
    //test a;
    
    constexpr std::variant<faitchier> v7;
    //constexpr std::variant<faitchier> v8 = v7;
    
    rtw::variant<watcher<1>, watcher<2>> v6 = v; // Non-trivial copy-construct

    std::cout << std::is_trivially_copy_constructible_v<decltype(v3)> << std::endl;
    std::cout << std::is_trivially_destructible_v<decltype(v)> << std::endl;
    
    constexpr std::variant<faitchier> v9;
    //v9.emplace<0>(3);
    
    std::variant<std::string, bool> v4("test");
    std::cout << v4.index() << std::endl;
*/


    using variant = rtw::variant<int, trivial_copy>;
    variant v10{std::in_place_index_t<1>{}};
    variant v11{v10};
    v10 = std::move(v11);
    
    
    return 0;
}