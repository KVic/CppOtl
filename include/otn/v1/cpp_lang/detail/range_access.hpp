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

#include <otn/v1/collection/detail/iterator.hpp>
#include <otn/v1/cpp_lang/origin.hpp>

namespace otn
{

inline namespace v1
{

namespace cpp_lang
{

// T - Type

// unified_optional
template <class T>
inline
collection::iterator<unified_optional<T>>
begin(unified_optional<T>& token) noexcept
{ return collection::iterator<unified_optional<T>>{token}; }

template <class T>
constexpr collection::iterator<unified_optional<T>>
end(unified_optional<T>&) noexcept
{ return collection::iterator<unified_optional<T>>{}; }

// unified_optional const
template <class T>
inline
collection::iterator<const unified_optional<T>>
begin(const unified_optional<T>& token) noexcept
{ return collection::iterator<const unified_optional<T>>{token}; }

template <class T>
constexpr collection::iterator<const unified_optional<T>>
end(const unified_optional<T>&) noexcept
{ return collection::iterator<const unified_optional<T>>{}; }

} // namespace cpp_lang

} // namespace v1

} // namespace otn
