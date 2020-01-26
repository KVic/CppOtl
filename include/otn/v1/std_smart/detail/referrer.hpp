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
#include <otn/v1/referrer/factory.hpp>

#include <otn/v1/std_smart/basis.hpp>
#include <otn/v1/std_smart/origin.hpp>

#include <otn/v1/ownership/names.hpp>

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
{
    static auto adapt(const std_smart::weak_optional<Y>& from) noexcept
    { return from.lock(); }

    static auto adapt(std_smart::weak_optional<Y>&& from) noexcept
    {
        auto proxy = from.lock();
        from.reset();
        return proxy;
    }
};

template <>
struct factory<basis::std_smart>
{
    template <class T, class BriefSpec, class ... Args>
    static auto make(Args&& ... args)
    {
        if constexpr (std::is_same_v<typename BriefSpec::ownership,
                                     ownership::unique>)
            return std_smart::unique_optional<T, typename BriefSpec::deleter>{
                new T(std::forward<Args>(args) ...)};
        else
        if constexpr (std::is_same_v<typename BriefSpec::ownership,
                                     ownership::shared>)
            return std::make_shared<T>(std::forward<Args>(args) ...);
        else
            static_assert(sizeof(T) == -1,
                          "referrer::factory<basis::std_smart> "
                          "is defined for the BriefSpec::ownership");
    }
};

} // namespace referrer

} // namespace v1

} // namespace otn
