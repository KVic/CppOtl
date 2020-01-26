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

#include <otn/v1/base/detail/token.hpp>

#include <functional>

namespace otn
{

inline namespace v1
{

namespace base
{

// T - Type

// ----- base::token <=> base::token -------------------------------------------
template <class T, class SpecT, class U, class SpecU>
inline bool operator==(const token<T, SpecT>& a,
                       const token<U, SpecU>& b) noexcept
{
    return otn::internal::to_address(a) == otn::internal::to_address(b);
}

template <class T, class SpecT, class U, class SpecU>
inline bool operator!=(const token<T, SpecT>& a,
                       const token<U, SpecU>& b) noexcept
{ return !(a == b); }

template <class T, class SpecT, class U, class SpecU>
inline bool operator<(const token<T, SpecT>& a,
                      const token<U, SpecU>& b) noexcept
{
    using E_T = typename token<T, SpecT>::element_type;
    using E_U = typename token<U, SpecU>::element_type;
    using V   = typename std::common_type_t<E_T*, E_U*>;
    return std::less<V>()(otn::internal::to_address(a),
                          otn::internal::to_address(b));
}

template <class T, class SpecT, class U, class SpecU>
inline bool operator>(const token<T, SpecT>& a,
                      const token<U, SpecU>& b) noexcept
{ return b < a; }

template <class T, class SpecT, class U, class SpecU>
inline bool operator<=(const token<T, SpecT>& a,
                       const token<U, SpecU>& b) noexcept
{ return !(b < a); }

template <class T, class SpecT, class U, class SpecU>
inline bool operator>=(const token<T, SpecT>& a,
                       const token<U, SpecU>& b) noexcept
{ return !(a < b); }
// ----- base::token <=> base::token -------------------------------------------

} // namespace base

} // namespace v1

} // namespace otn
