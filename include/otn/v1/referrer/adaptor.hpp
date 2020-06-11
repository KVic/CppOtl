/*
 * MIT License
 *
 * Copyright (c) 2018-2020 Viktor Kireev
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <otn/v1/support/type_traits.hpp>

#include <utility>

namespace otn
{

inline namespace v1
{

namespace referrer
{

template <class To, class From, class = void>
struct adaptor
{
    static constexpr bool is_copy_constructible =
        std::is_constructible_v<To, const From&>;
    static constexpr bool is_move_constructible =
        std::is_constructible_v<To, From&&>;
    static constexpr bool is_copy_assignable =
        is_copy_constructible && std::is_swappable_v<To>;
    static constexpr bool is_move_assignable =
        is_move_constructible && std::is_swappable_v<To>;

    static constexpr bool is_nothrow_copy_constructible =
        std::is_nothrow_constructible_v<To, const From&>;
    static constexpr bool is_nothrow_move_constructible =
        std::is_nothrow_constructible_v<To, From&&>;

    // TODO: Replace 'auto -> To' when Concepts become available.
    static auto adapt(const From& from) noexcept(is_nothrow_copy_constructible)
    { return To{from}; }

    // TODO: Replace 'auto -> To' when Concepts become available.
    static auto adapt(From&& from) noexcept(is_nothrow_move_constructible)
    { return To{std::move(from)}; }
};

template <class To, class From>
inline constexpr bool is_adaptor_copy_nothrow =
    adaptor<To, otn::remove_cvref_t<From>>::is_nothrow_copy_constructible;

template <class To, class From>
inline constexpr bool is_adaptor_move_nothrow =
    adaptor<To, otn::remove_cvref_t<From>>::is_nothrow_move_constructible;

template <class To, class From>
inline constexpr bool is_adaptor_nothrow =
    std::is_lvalue_reference_v<From>
    ? is_adaptor_copy_nothrow<To, From>
    : is_adaptor_move_nothrow<To, From>;

template <class To, class From>
inline To adapt(From&& from) noexcept(is_adaptor_nothrow<To, From>)
{
    return adaptor<To, otn::remove_cvref_t<From>>::
           adapt(std::forward<From>(from));
}

} // namespace referrer

} // namespace v1

} // namespace otn
