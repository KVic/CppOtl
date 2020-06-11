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

#include <otn/v1/cpp_lang/internal/storage_optional.hpp>

#include <memory>

namespace otn
{

inline namespace v1
{

namespace cpp_lang
{

template <class T>
struct thin_optional
{
    using element_type = T;

    internal::storage_optional<element_type> storage{};

    // Modifiers
    static constexpr bool is_swappable =
        std::is_move_constructible_v<element_type>
        && std::is_swappable_v<element_type>;
    static constexpr bool is_nothrow_swappable =
        std::is_nothrow_move_constructible_v<element_type>
        && std::is_nothrow_swappable_v<element_type>;

    void swap(thin_optional& other) noexcept(is_nothrow_swappable)
    { storage.holder.swap(other.storage.holder); }

    // Conversion functions
    template <class Y>
    constexpr explicit operator Y*() const & noexcept
    { return *this ? std::addressof(**this) : nullptr; }

    template <class Y>
    operator Y*() && = delete;

    // Observers
    constexpr element_type& operator*() const noexcept
    { return *storage.holder; }

    constexpr element_type* operator->() const noexcept
    { return static_cast<element_type*>(*this); }

    explicit constexpr operator bool() const noexcept
    { return static_cast<bool>(storage.holder); }
};

} // namespace cpp_lang

} // namespace v1

} // namespace otn
