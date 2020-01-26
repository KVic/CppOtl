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

#include <otn/v1/support/pointer_traits.hpp>
#include <otn/v1/std_smart/origin.hpp>

namespace otn
{

inline namespace v1
{

namespace internal
{

// T - Type

template <class T, class Deleter>
struct pointer_traits<std_smart::unique_optional<T, Deleter>>
    : std::pointer_traits<std_smart::unique_optional<T, Deleter>>
{
    using std_traits =
        std::pointer_traits<std_smart::unique_optional<T, Deleter>>;

    using typename std_traits::pointer;
    using typename std_traits::element_type;

    static element_type* to_address(const pointer& p) noexcept
    { return p.get(); }
};

template <class T>
struct pointer_traits<std_smart::shared_optional<T>>
    : std::pointer_traits<std_smart::shared_optional<T>>
{
    using std_traits =
        std::pointer_traits<std_smart::shared_optional<T>>;

    using typename std_traits::pointer;
    using typename std_traits::element_type;

    static element_type* to_address(const pointer& p) noexcept
    { return p.get(); }
};

} // namespace internal

} // namespace v1

} // namespace otn
