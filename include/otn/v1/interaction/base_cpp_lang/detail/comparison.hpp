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
#include <otn/v1/cpp_lang/unified_unknown.hpp>

#include <functional>

namespace otn
{

inline namespace v1
{

namespace base
{

// ----- base::token <=> nullptr -----------------------------------------------
template <class TokenT, class U>
inline bool operator==(const TokenT& a,
                       const cpp_lang::unified_unknown<U>& b) noexcept
{ return otn::internal::to_address(a) == b; }

template <class TokenT, class U>
inline bool operator==(const cpp_lang::unified_unknown<U>& a,
                       const TokenT& b) noexcept
{ return b == a; }

template <class TokenT, class U>
inline bool operator!=(const TokenT& a,
                       const cpp_lang::unified_unknown<U>& b) noexcept
{ return !(a == b); }

template <class TokenT, class U>
inline bool operator!=(const cpp_lang::unified_unknown<U>& a,
                       const TokenT& b) noexcept
{ return !(a == b); }

template <class TokenT, class U>
inline bool operator<(const TokenT& a,
                      const cpp_lang::unified_unknown<U>& b) noexcept
{
    using E_T = typename std::pointer_traits<TokenT>::element_type;
    using E_U = typename std::pointer_traits<cpp_lang::unified_unknown<U>>::element_type;
    using V   = typename std::common_type_t<E_T*, E_U*>;
    return std::less<V>()(otn::internal::to_address(a), b);
}

template <class TokenT, class U>
inline bool operator<(const cpp_lang::unified_unknown<U>& a,
                      const TokenT& b) noexcept
{
    using E_T = typename std::pointer_traits<TokenT>::element_type;
    using E_U = typename std::pointer_traits<cpp_lang::unified_unknown<U>>::element_type;
    using V   = typename std::common_type_t<E_T*, E_U*>;
    return std::less<V>()(a, otn::internal::to_address(b));
}

template <class TokenT, class U>
inline bool operator>(const TokenT& a,
                      const cpp_lang::unified_unknown<U>& b) noexcept
{ return b < a; }

template <class TokenT, class U>
inline bool operator>(const cpp_lang::unified_unknown<U>& a,
                      const TokenT& b) noexcept
{ return b < a; }

template <class TokenT, class U>
inline bool operator<=(const TokenT& a,
                       const cpp_lang::unified_unknown<U>& b) noexcept
{ return !(b < a); }

template <class TokenT, class U>
inline bool operator<=(const cpp_lang::unified_unknown<U>& a,
                       const TokenT& b) noexcept
{ return !(b < a); }

template <class TokenT, class U>
inline bool operator>=(const TokenT& a,
                       const cpp_lang::unified_unknown<U>& b) noexcept
{ return !(a < b); }

template <class TokenT, class U>
inline bool operator>=(const cpp_lang::unified_unknown<U>& a,
                       const TokenT& b) noexcept
{ return !(a < b); }
// ----- base::token <=> nullptr -----------------------------------------------

// ----- base::token <=> nullptr -----------------------------------------------
template <class T, class SpecT>
inline bool
operator==(const token<T, SpecT>& a, std::nullptr_t) noexcept
{ return !a; }

template <class T, class SpecT>
inline bool
operator==(std::nullptr_t, const token<T, SpecT>& a) noexcept
{ return !a; }

template <class T, class SpecT>
inline bool
operator!=(const token<T, SpecT>& a, std::nullptr_t) noexcept
{ return static_cast<bool>(a); }

template <class T, class SpecT>
inline bool
operator!=(std::nullptr_t, const token<T, SpecT>& a) noexcept
{ return static_cast<bool>(a); }

template <class T, class SpecT>
inline bool
operator<(const token<T, SpecT>& a, std::nullptr_t) noexcept
{
    using E_T = typename std::pointer_traits<token<T, SpecT>>::element_type;
    return std::less<E_T*>()(otn::internal::to_address(a), nullptr);
}

template <class T, class SpecT>
inline bool
operator<(std::nullptr_t, const token<T, SpecT>& a) noexcept
{
    using E_T = typename std::pointer_traits<token<T, SpecT>>::element_type;
    return std::less<E_T*>()(nullptr, otn::internal::to_address(a));
}

template <class T, class SpecT>
inline bool
operator>(const token<T, SpecT>& a, std::nullptr_t) noexcept
{ return nullptr < a; }

template <class T, class SpecT>
inline bool
operator>(std::nullptr_t, const token<T, SpecT>& a) noexcept
{ return a < nullptr; }

template <class T, class SpecT>
inline bool
operator<=(const token<T, SpecT>& a, std::nullptr_t) noexcept
{ return !(nullptr < a); }

template <class T, class SpecT>
inline bool
operator<=(std::nullptr_t, const token<T, SpecT>& a) noexcept
{ return !(a < nullptr); }

template <class T, class SpecT>
inline bool
operator>=(const token<T, SpecT>& a, std::nullptr_t) noexcept
{ return !(a < nullptr); }

template <class T, class SpecT>
inline bool
operator>=(std::nullptr_t, const token<T, SpecT>& a) noexcept
{ return !(nullptr < a); }
// ----- base::token <=> nullptr -----------------------------------------------

} // namespace base

} // namespace v1

} // namespace otn
