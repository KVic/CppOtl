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

#include <otn/v1/cpp_lang/referrer.hpp>
#include <otn/v1/cpp_lang/origin.hpp>

namespace otn
{

inline namespace v1
{

namespace referrer
{

// T - Type

// cpp_lang::unified_unknown<T> <- cpp_lang::thin_any<Y>
template <class T, class Y>
struct adaptor<cpp_lang::unified_unknown<T>,
               cpp_lang::thin_single<Y>>
    : adaptor_cpp_lang_observer_any_owner<cpp_lang::unified_unknown<T>,
                                          cpp_lang::thin_single<Y>> {};

template <class T, class Y>
struct adaptor<cpp_lang::unified_unknown<T>,
               cpp_lang::thin_optional<Y>>
    : adaptor_cpp_lang_observer_any_owner<cpp_lang::unified_unknown<T>,
                                          cpp_lang::thin_optional<Y>> {};

// cpp_lang::unified_optional<T> <- cpp_lang::thin_any<Y>
template <class T, class Y>
struct adaptor<cpp_lang::unified_optional<T>,
               cpp_lang::thin_single<Y>>
    : adaptor_cpp_lang_observer_any_owner<cpp_lang::unified_optional<T>,
                                          cpp_lang::thin_single<Y>> {};

template <class T, class Y>
struct adaptor<cpp_lang::unified_optional<T>,
               cpp_lang::thin_optional<Y>>
    : adaptor_cpp_lang_observer_any_owner<cpp_lang::unified_optional<T>,
                                          cpp_lang::thin_optional<Y>> {};

// cpp_lang::thin_optional<T> <- cpp_lang::thin_any<Y>
template <class T, class Y>
struct adaptor<cpp_lang::thin_optional<T>,
               cpp_lang::thin_optional<Y>>
    : traits_united_owner_any_owner<T, Y>
{
    using traits = traits_united_owner_any_owner<T, Y>;

    static cpp_lang::thin_optional<T>
    adapt(const cpp_lang::thin_optional<Y>& from) = delete;

    static cpp_lang::thin_optional<T>
    adapt(cpp_lang::thin_optional<Y>&& from) noexcept(
        traits::is_nothrow_move_constructible)
    {
        return cpp_lang::thin_optional<T>{
            cpp_lang::clear_optional<T>{
                std::move(from.storage.holder)}};
    }
};

template <class T, class Y>
struct adaptor<cpp_lang::thin_optional<T>,
               cpp_lang::thin_single<Y>>
    : traits_united_owner_any_owner<T, Y>
{
    using traits = traits_united_owner_any_owner<T, Y>;

    static cpp_lang::thin_optional<T>
    adapt(const cpp_lang::thin_single<Y>& from) = delete;

    static cpp_lang::thin_optional<T>
    adapt(cpp_lang::thin_single<Y>&& from) noexcept(
        traits::is_nothrow_move_constructible)
    {
        return cpp_lang::thin_optional<T>{
            cpp_lang::clear_optional<T>{std::move(*from)}};
    }
};

// cpp_lang::thin_single<T> <- cpp_lang::thin_any<Y>
template <class T, class Y>
struct adaptor<cpp_lang::thin_single<T>,
               cpp_lang::thin_optional<Y>>
    : traits_united_owner_any_owner<T, Y>
{
    using traits = traits_united_owner_any_owner<T, Y>;

    static cpp_lang::thin_single<T>
    adapt(const cpp_lang::thin_optional<Y>& from) = delete;

    static cpp_lang::thin_single<T>
    adapt(cpp_lang::thin_optional<Y>&& from) noexcept(
        traits::is_nothrow_move_constructible)
    {
        cpp_lang::clear_optional<Y> temp{std::move(from.storage.holder)};
        return cpp_lang::thin_single<T>{Y{std::move(*temp)}};
    }
};

template <class T, class Y>
struct adaptor<cpp_lang::thin_single<T>,
               cpp_lang::thin_single<Y>>
    : traits_united_owner_any_owner<T, Y>
{
    using traits = traits_united_owner_any_owner<T, Y>;

    static cpp_lang::thin_single<T>
    adapt(const cpp_lang::thin_single<Y>& from) = delete;

    static cpp_lang::thin_single<T>
    adapt(cpp_lang::thin_single<Y>&& from) noexcept(
        traits::is_nothrow_move_constructible)
    { return cpp_lang::thin_single<T>{T{std::move(*from)}}; }
};

template <class T>
struct factory<cpp_lang::thin_optional<T>>
{
    template <class Y, class ... Args>
    static constexpr bool is_constructible =
        (  std::is_same_v<T, Y> // std::optional<T>{Y{Args}} may be invalid.
        && std::is_constructible_v<T, Args ...>);
    // NOTE: Doesn't work due to copy elision.
    // && std::is_constructible_v<T, Y>

    template <class Y, class ... Args>
    static constexpr bool is_nothrow_constructible =
        std::is_nothrow_constructible_v<T, Args ...>;
    // NOTE: Doesn't work due to copy elision.
    // && std::is_nothrow_constructible_v<T, Y>

    template <class Y, class ... Args>
    static constexpr cpp_lang::thin_optional<T>
    make(Args&& ... args) noexcept(is_nothrow_constructible<Y, Args ...>)
    {
        return cpp_lang::thin_optional<T>{
            cpp_lang::clear_optional<T>{
                std::in_place, std::forward<Args>(args) ...}};
    }
};

template <class T>
struct factory<cpp_lang::thin_single<T>>
{
    template <class Y, class ... Args>
    static constexpr bool is_constructible =
        std::is_constructible_v<Y, Args ...>;
    // NOTE: Doesn't work due to copy elision.
    // && std::is_constructible_v<T, Y>

    template <class Y, class ... Args>
    static constexpr bool is_nothrow_constructible =
        std::is_nothrow_constructible_v<Y, Args ...>;
    // NOTE: Doesn't work due to copy elision.
    // && std::is_nothrow_constructible_v<T, Y>

    template <class Y, class ... Args>
    static constexpr cpp_lang::thin_single<T>
    make(Args&& ... args) noexcept(is_nothrow_constructible<Y, Args ...>)
    { return cpp_lang::thin_single<T>{Y{std::forward<Args>(args) ...}}; }
};

} // namespace referrer

} // namespace v1

} // namespace otn
