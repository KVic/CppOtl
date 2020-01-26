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

#include <otn/v1/cpp_lang/origin.hpp>

#include <otn/v1/support/pointer_traits.hpp>

#include <functional>

namespace otn
{

inline namespace v1
{

namespace cpp_lang
{

// ----- cpp_lang::some <=> some::some -----------------------------------------
template <class TokenT, class TokenU>
inline bool operator==(const TokenT& a, const TokenU& b) noexcept
{ return otn::internal::to_address(a) == otn::internal::to_address(b); }

template <class TokenT, class TokenU>
inline bool operator!=(const TokenT& a, const TokenU& b) noexcept
{ return !(a == b); }

template <class TokenT, class TokenU>
inline bool operator<(const TokenT& a, const TokenU& b) noexcept
{
    using E_T = typename std::pointer_traits<TokenT>::element_type;
    using E_U = typename std::pointer_traits<TokenU>::element_type;
    using V   = typename std::common_type_t<E_T*, E_U*>;
    return std::less<V>()(otn::internal::to_address(a),
                          otn::internal::to_address(b));
}

template <class TokenT, class TokenU>
inline bool operator>(const TokenT& a, const TokenU& b) noexcept
{ return b < a; }

template <class TokenT, class TokenU>
inline bool operator<=(const TokenT& a, const TokenU& b) noexcept
{ return !(b < a); }

template <class TokenT, class TokenU>
inline bool operator>=(const TokenT& a, const TokenU& b) noexcept
{ return !(a < b); }
// ----- cpp_lang::some <=> some::some -----------------------------------------

// ----- cpp_lang::some <=> std::nullptr_t -------------------------------------
template <class TokenT>
inline bool
operator==(const TokenT& a, std::nullptr_t) noexcept
{ return !a; }

template <class TokenT>
inline bool
operator==(std::nullptr_t, const TokenT& a) noexcept
{ return !a; }

template <class TokenT>
inline bool
operator!=(const TokenT& a, std::nullptr_t) noexcept
{ return static_cast<bool>(a); }

template <class TokenT>
inline bool
operator!=(std::nullptr_t, const TokenT& a) noexcept
{ return static_cast<bool>(a); }

template <class TokenT>
inline bool
operator<(const TokenT& a, std::nullptr_t) noexcept
{
    using E_T = typename std::pointer_traits<TokenT>::element_type;
    return std::less<E_T*>()(otn::internal::to_address(a), nullptr);
}

template <class TokenT>
inline bool
operator<(std::nullptr_t, const TokenT& a) noexcept
{
    using E_T = typename std::pointer_traits<TokenT>::element_type;
    return std::less<E_T*>()(nullptr, otn::internal::to_address(a));
}

template <class TokenT>
inline bool
operator>(const TokenT& a, std::nullptr_t) noexcept
{ return nullptr < a; }

template <class TokenT>
inline bool
operator>(std::nullptr_t, const TokenT& a) noexcept
{ return a < nullptr; }

template <class TokenT>
inline bool
operator<=(const TokenT& a, std::nullptr_t) noexcept
{ return !(nullptr < a); }

template <class TokenT>
inline bool
operator<=(std::nullptr_t, const TokenT& a) noexcept
{ return !(a < nullptr); }

template <class TokenT>
inline bool
operator>=(const TokenT& a, std::nullptr_t) noexcept
{ return !(a < nullptr); }

template <class TokenT>
inline bool
operator>=(std::nullptr_t, const TokenT& a) noexcept
{ return !(nullptr < a); }
// ----- cpp_lang::some <=> std::nullptr_t -------------------------------------

} // namespace cpp_lang

} // namespace v1

} // namespace otn
