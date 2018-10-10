#ifndef ENABLE_SPECIAL_METHOD_HPP
#define ENABLE_SPECIAL_METHOD_HPP


#include <type_traits>


namespace rtw::detail
{
    template<bool copy_constructible,
        bool move_constructible,
        bool copy_assignable,
        bool move_assignable>
    struct enable_special_method_impl;
    
    template<typename... Ts>
    using enable_special_method = enable_special_method_impl<
        (std::is_copy_constructible_v<Ts> && ...),
        (std::is_move_constructible_v<Ts> && ...),
        (std::is_copy_assignable_v<Ts> && ...),
        (std::is_move_assignable_v<Ts> && ...)
    >;

    template<>
    struct enable_special_method_impl<true, true, true, true>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = default;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = default;
    };
    template<>
    struct enable_special_method_impl<true, true, true, false>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = default;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = delete;
    };
    template<>
    struct enable_special_method_impl<true, true, false, true>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = default;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = default;
    };
    template<>
    struct enable_special_method_impl<true, true, false, false>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = default;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = delete;
    };
    template<>
    struct enable_special_method_impl<true, false, true, true>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = delete;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = default;
    };
    template<>
    struct enable_special_method_impl<true, false, true, false>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = delete;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = delete;
    };
    template<>
    struct enable_special_method_impl<true, false, false, true>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = delete;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = default;
    };
    template<>
    struct enable_special_method_impl<true, false, false, false>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = delete;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = delete;
    };
    template<>
    struct enable_special_method_impl<false, true, true, true>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = default;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = default;
    };
    template<>
    struct enable_special_method_impl<false, true, true, false>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = default;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = delete;
    };
    template<>
    struct enable_special_method_impl<false, true, false, true>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = default;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = default;
    };
    template<>
    struct enable_special_method_impl<false, true, false, false>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = default;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = delete;
    };
    template<>
    struct enable_special_method_impl<false, false, true, true>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = delete;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = default;
    };
    template<>
    struct enable_special_method_impl<false, false, true, false>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = delete;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = default;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = delete;
    };
    template<>
    struct enable_special_method_impl<false, false, false, true>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = delete;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = default;
    };
    template<>
    struct enable_special_method_impl<false, false, false, false>
    {
        enable_special_method_impl() = default;
        enable_special_method_impl(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl(enable_special_method_impl&&) noexcept = delete;
        enable_special_method_impl& operator=(const enable_special_method_impl&) noexcept = delete;
        enable_special_method_impl& operator=(enable_special_method_impl&&) noexcept = delete;
    };
}
#endif // ENABLE_SPECIAL_METHOD_HPP