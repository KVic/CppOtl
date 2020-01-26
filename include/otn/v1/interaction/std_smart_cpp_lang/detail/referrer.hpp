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

#include <otn/v1/cpp_lang/origin.hpp>
#include <otn/v1/std_smart/origin.hpp>

namespace otn
{

inline namespace v1
{

namespace referrer
{

// T - Type

// cpp_lang::unified_unknown<T> <- std_smart::some_optional<Y>
template <class T, class Y, class Deleter>
struct adaptor<cpp_lang::unified_unknown<T>,
               std_smart::unique_optional<Y, Deleter>>
{
    static auto adapt(const std_smart::unique_optional<Y, Deleter>& from) noexcept
    { return from.get(); }

    static void adapt(std_smart::unique_optional<Y, Deleter>&& from) = delete;
};

template <class T, class Y>
struct adaptor<cpp_lang::unified_unknown<T>,
               std_smart::shared_optional<Y>>
{
    static auto adapt(const std_smart::shared_optional<Y>& from) noexcept
    { return from.get(); }

    static void adapt(std_smart::shared_optional<Y>&& from) = delete;
};

template <class T, class Y>
struct adaptor<cpp_lang::unified_unknown<T>,
               std_smart::weak_optional<Y>>
{
    static auto adapt(const std_smart::weak_optional<Y>& from) noexcept
    { return from.lock().get(); }

    static auto adapt(std_smart::weak_optional<Y>&& from) noexcept
    {
        auto result = adapt(std::as_const(from));
        // TODO: Leave a value in the from?
        from.reset();
        return result;
    }
};

// cpp_lang::unified_optional<T> <- std_smart::some_optional<Y>
template <class T, class Y, class Deleter>
struct adaptor<cpp_lang::unified_optional<T>,
               std_smart::unique_optional<Y, Deleter>>
{
    static auto adapt(const std_smart::unique_optional<Y, Deleter>& from) noexcept
    { return from.get(); }

    static void adapt(std_smart::unique_optional<Y, Deleter>&& from) = delete;
};

template <class T, class Y>
struct adaptor<cpp_lang::unified_optional<T>,
               std_smart::shared_optional<Y>>
{
    static auto adapt(const std_smart::shared_optional<Y>& from) noexcept
    { return from.get(); }

    static void adapt(std_smart::shared_optional<Y>&& from) = delete;
};

template <class T, class Y>
struct adaptor<cpp_lang::unified_optional<T>,
               std_smart::weak_optional<Y>>
{
    static auto adapt(const std_smart::weak_optional<Y>& from) noexcept
    { return from.lock().get(); }

    static auto adapt(std_smart::weak_optional<Y>&& from) noexcept
    {
        auto result = adapt(std::as_const(from));
        // TODO: Leave a value in the from?
        from.reset();
        return result;
    }
};

} // namespace referrer

} // namespace v1

} // namespace otn
