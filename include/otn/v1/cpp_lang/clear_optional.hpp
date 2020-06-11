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

#include <optional>

namespace otn
{

inline namespace v1
{

namespace cpp_lang
{

template <class T>
class clear_optional : public std::optional<T>
{
private:
    using parent_type = std::optional<T>;

public:
    using parent_type::optional;
    using parent_type::operator=;

    constexpr clear_optional(clear_optional&& other) noexcept(
        std::is_nothrow_move_constructible_v<T>)
        : parent_type{std::move(other)}
    { other.reset(); }

    template <class Y>
    constexpr clear_optional(clear_optional<Y>&& other) noexcept(
        std::is_nothrow_constructible_v<T, Y&&>)
        : parent_type{std::move(other)}
    { other.reset(); }

    constexpr clear_optional& operator=(clear_optional&& other) noexcept(
        (  std::is_nothrow_move_constructible_v<T>
        && std::is_nothrow_move_assignable_v<T>))
    {
        parent_type::operator=(std::move(other));
        other.reset();
        return *this;
    }

    template <class Y>
    constexpr clear_optional& operator=(clear_optional<Y>&& other) noexcept(
        (  std::is_nothrow_constructible_v<T, Y&&>
        && std::is_nothrow_assignable_v<T, Y&&>))
    {
        parent_type::operator=(std::move(other));
        other.reset();
        return *this;
    }
};

} // namespace cpp_lang

} // namespace v1

} // namespace otn
