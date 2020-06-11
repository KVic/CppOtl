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
#include <otn/v1/cpp_lang/referrer.hpp>
#include <otn/v1/interaction/std_smart_cpp_lang/referrer.hpp>
#include <otn/v1/cpp_lang/origin.hpp>
#include <otn/v1/std_smart/origin.hpp>

#include <otn/v1/support/assert.hpp>

namespace otn
{

inline namespace v1
{

namespace referrer
{

// T - Type
// Y - Type

// cpp_lang::unified_unknown<T> <- std_smart::some_optional<Y>
template <class T, class Y, class Deleter>
struct adaptor<cpp_lang::unified_unknown<T>,
               std_smart::unique_optional<Y, Deleter>>
    : adaptor_cpp_lang_observer_any_owner<cpp_lang::unified_unknown<T>,
                                          std_smart::unique_optional<Y, Deleter>> {};

template <class T, class Y>
struct adaptor<cpp_lang::unified_unknown<T>,
               std_smart::shared_optional<Y>>
    : adaptor_cpp_lang_observer_any_owner<cpp_lang::unified_unknown<T>,
                                          std_smart::shared_optional<Y>> {};

template <class T, class Y>
struct adaptor<cpp_lang::unified_unknown<T>,
               std_smart::weak_optional<Y>>
    : adaptor_cpp_lang_observer_std_smart_observer<cpp_lang::unified_unknown<T>,
                                                   std_smart::weak_optional<Y>> {};

// cpp_lang::unified_optional<T> <- std_smart::some_optional<Y>
template <class T, class Y, class Deleter>
struct adaptor<cpp_lang::unified_optional<T>,
               std_smart::unique_optional<Y, Deleter>>
    : adaptor_cpp_lang_observer_any_owner<cpp_lang::unified_optional<T>,
                                          std_smart::unique_optional<Y, Deleter>> {};

template <class T, class Y>
struct adaptor<cpp_lang::unified_optional<T>,
               std_smart::shared_optional<Y>>
    : adaptor_cpp_lang_observer_any_owner<cpp_lang::unified_optional<T>,
                                          std_smart::shared_optional<Y>> {};

template <class T, class Y>
struct adaptor<cpp_lang::unified_optional<T>,
               std_smart::weak_optional<Y>>
    : adaptor_cpp_lang_observer_std_smart_observer<cpp_lang::unified_optional<T>,
                                                   std_smart::weak_optional<Y>> {};

// cpp_lang::thin_any<T> <- std_smart::unique_optional<Y>
template <class T, class Y, class Deleter>
struct adaptor<cpp_lang::thin_optional<T>,
               std_smart::unique_optional<Y, Deleter>>
    : traits_united_owner_any_owner<T, Y>
{
    using traits = traits_united_owner_any_owner<T, Y>;

    static void adapt(const std_smart::unique_optional<Y, Deleter>& from) = delete;

    static cpp_lang::thin_optional<T>
    adapt(std_smart::unique_optional<Y, Deleter>&& from) noexcept(
        traits::is_nothrow_move_constructible)
    {
        if (!from)
            return cpp_lang::thin_optional<T>{};

        std_smart::unique_optional<Y, Deleter> temp{std::move(from)};
        return cpp_lang::thin_optional<T>{
            cpp_lang::clear_optional<T>{std::move(*temp)}};
    }
};

template <class T, class Y, class Deleter>
struct adaptor<cpp_lang::thin_single<T>,
               std_smart::unique_optional<Y, Deleter>>
    : traits_united_owner_any_owner<T, Y>
{
    using traits = traits_united_owner_any_owner<T, Y>;

    static void adapt(const std_smart::unique_optional<Y, Deleter>& from) = delete;

    static cpp_lang::thin_single<T>
    adapt(std_smart::unique_optional<Y, Deleter>&& from) noexcept(
        traits::is_nothrow_move_constructible)
    {
    #if (!defined NDEBUG)
        if (!from)
        {
            const std_smart::unique_optional<Y, Deleter>& source = from;
            OTN_ASSERT(construct_from_valued_referrer(source));

        #if defined TOKEN_TEST_ASSERT
            if constexpr (std::is_default_constructible_v<Y>)
                return cpp_lang::thin_single<T>{Y{}};
            else
                return cpp_lang::thin_single<T>{*cpp_lang::thin_optional<Y>{}};

        #endif
        }

    #endif

        std_smart::unique_optional<Y, Deleter> temp{std::move(from)};
        return cpp_lang::thin_single<T>{T{std::move(*temp)}};
    }

#if (!defined NDEBUG)

protected:
    static constexpr bool construct_from_valued_referrer(
        const std_smart::unique_optional<Y, Deleter>& referrer) noexcept
    { return static_cast<bool>(referrer); }
#endif
};

// std_smart::unique_optional<T> <- cpp_lang::thin_any<Y>
template <class T, class Y, class Deleter>
struct adaptor<std_smart::unique_optional<T, Deleter>,
               cpp_lang::thin_optional<Y>>
    : traits_divided_owner_united_owner<T, Y>
{
    static void adapt(const cpp_lang::thin_optional<Y>& from) = delete;

    static std_smart::unique_optional<T, Deleter>
    adapt(cpp_lang::thin_optional<Y>&& from)
    {
        if (!from)
            return std_smart::unique_optional<T, Deleter>{};

        cpp_lang::clear_optional<Y> temp{std::move(from.storage.holder)};
        if constexpr (std::is_polymorphic_v<T>)
            return std_smart::unique_optional<T, Deleter>{
                new Y(std::move(*temp))};
        else
            return std_smart::unique_optional<T, Deleter>{
                new T(std::move(*temp))};
    }
};

template <class T, class Y, class Deleter>
struct adaptor<std_smart::unique_optional<T, Deleter>,
               cpp_lang::thin_single<Y>>
    : traits_divided_owner_united_owner<T, Y>
{
    static void adapt(const cpp_lang::thin_single<Y>& from) = delete;

    static std_smart::unique_optional<T, Deleter>
    adapt(cpp_lang::thin_single<Y>&& from)
    {
        if constexpr (std::is_polymorphic_v<T>)
            return std_smart::unique_optional<T, Deleter>{
                new Y(std::move(*from))};
        else
            return std_smart::unique_optional<T, Deleter>{
                new T(std::move(*from))};
    }
};

// std_smart::shared_optional<T> <- cpp_lang::thin_any<Y>
template <class T, class Y>
struct adaptor<std_smart::shared_optional<T>,
               cpp_lang::thin_optional<Y>>
    : traits_divided_owner_united_owner<T, Y>
{
    static void adapt(const cpp_lang::thin_optional<Y>& from) = delete;

    static std_smart::shared_optional<T>
    adapt(cpp_lang::thin_optional<Y>&& from)
    {
        if (!from)
            return std_smart::shared_optional<T>{};

        cpp_lang::clear_optional<Y> temp{std::move(from.storage.holder)};
        if constexpr (std::is_polymorphic_v<T>)
            return std_smart::shared_optional<T>{
                std::make_shared<Y>(std::move(*temp))};
        else
            return std::make_shared<T>(std::move(*temp));
    }
};

template <class T, class Y>
struct adaptor<std_smart::shared_optional<T>,
               cpp_lang::thin_single<Y>>
    : traits_divided_owner_united_owner<T, Y>
{
    static void adapt(const cpp_lang::thin_single<Y>& from) = delete;

    static std_smart::shared_optional<T>
    adapt(cpp_lang::thin_single<Y>&& from)
    {
        if constexpr (std::is_polymorphic_v<T>)
            return std_smart::shared_optional<T>{
                std::make_shared<Y>(std::move(*from))};
        else
            return std::make_shared<T>(std::move(*from));
    }
};

} // namespace referrer

} // namespace v1

} // namespace otn
