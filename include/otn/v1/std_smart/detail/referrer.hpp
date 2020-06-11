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

#include <otn/v1/referrer/adaptor.hpp>
#include <otn/v1/referrer/adaptor_traits.hpp>
#include <otn/v1/referrer/factory.hpp>

#include <otn/v1/std_smart/origin.hpp>

namespace otn
{

inline namespace v1
{

namespace referrer
{

// T - Type

template <class T, class Y>
struct adaptor<std_smart::shared_optional<T>,
               std_smart::weak_optional<Y>>
    : traits_divided_any_divided_observer<T, Y>
{
    static std_smart::shared_optional<T>
    adapt(const std_smart::weak_optional<Y>& from) noexcept
    { return std_smart::shared_optional<T>{from.lock()}; }

    static std_smart::shared_optional<T>
    adapt(std_smart::weak_optional<Y>&& from) noexcept
    {
        std_smart::weak_optional<Y> temp{std::move(from)};
        return std_smart::shared_optional<T>{temp.lock()};
    }
};

template <class T, class Deleter>
struct factory<std_smart::unique_optional<T, Deleter>>
{
    template <class Y, class ... Args>
    static constexpr bool is_constructible =
        (  std::is_constructible_v<Y, Args ...>
        && is_elements_convertible<Y, T>);

    template <class Y, class ... Args>
    static constexpr bool is_nothrow_constructible = false;

    template <class Y, class ... Args>
    static std_smart::unique_optional<T, Deleter>
    make(Args&& ... args)
    {
        return std_smart::unique_optional<T, Deleter>{
            new Y(std::forward<Args>(args) ...)};
    }
};

template <class T>
struct factory<std_smart::shared_optional<T>>
{
    template <class Y, class ... Args>
    static constexpr bool is_constructible =
        (  std::is_constructible_v<Y, Args ...>
        && is_elements_convertible<Y, T>);

    template <class Y, class ... Args>
    static constexpr bool is_nothrow_constructible = false;

    template <class Y, class ... Args>
    static std_smart::shared_optional<T>
    make(Args&& ... args)
    {
        return std_smart::shared_optional<T>{
            std::make_shared<Y>(std::forward<Args>(args) ...)};
    }
};

} // namespace referrer

} // namespace v1

} // namespace otn
