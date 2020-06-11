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

#include <otn/v1/element/traits.hpp>

namespace otn
{

inline namespace v1
{

namespace referrer
{

// divided_observer <- any_owner traits
template <class T, class Y>
struct traits_divided_observer_any_owner
{
    static constexpr bool is_copy_constructible = is_elements_convertible<Y, T>;
    static constexpr bool is_move_constructible = false;
    static constexpr bool is_copy_assignable    = is_copy_constructible;
    static constexpr bool is_move_assignable    = false;

    static constexpr bool is_nothrow_copy_constructible = true;
    static constexpr bool is_nothrow_move_constructible = false;
};

// divided_any <- any_observer traits
template <class T, class Y>
struct traits_divided_any_divided_observer
{
    static constexpr bool is_copy_constructible = is_elements_convertible<Y, T>;
    static constexpr bool is_move_constructible = is_copy_constructible;
    static constexpr bool is_copy_assignable    = is_copy_constructible;
    static constexpr bool is_move_assignable    = is_copy_constructible;

    static constexpr bool is_nothrow_copy_constructible = true;
    static constexpr bool is_nothrow_move_constructible = true;
};

// united_owner <- any_owner traits
template <class T, class Y>
struct traits_united_owner_any_owner
{
    static constexpr bool is_copy_constructible = false;
    static constexpr bool is_move_constructible =
        std::is_constructible_v<T, Y&&>;
    static constexpr bool is_copy_assignable = false;
    static constexpr bool is_move_assignable =
        is_move_constructible && std::is_swappable_v<T>;

    static constexpr bool is_nothrow_copy_constructible = false;
    static constexpr bool is_nothrow_move_constructible =
        std::is_nothrow_constructible_v<T, Y&&>;
};

// divided_owner <- united_owner traits
template <class T, class Y>
struct traits_divided_owner_united_owner
{
    static constexpr bool is_copy_constructible = false;
    static constexpr bool is_move_constructible =
        std::is_polymorphic_v<T>
        ? is_elements_convertible<Y, T>
        : std::is_constructible_v<T, Y&&>;
    static constexpr bool is_copy_assignable = false;
    static constexpr bool is_move_assignable = is_move_constructible;

    static constexpr bool is_nothrow_copy_constructible = false;
    static constexpr bool is_nothrow_move_constructible = false;
};

} // namespace referrer

} // namespace v1

} // namespace otn
