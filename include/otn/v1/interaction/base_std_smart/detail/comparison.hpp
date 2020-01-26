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

#include <otn/v1/std_smart/origin.hpp>

#include <otn/v1/support/pointer_traits.hpp>

namespace otn
{

inline namespace v1
{

namespace base
{

// ----- base::some <=> std_smart::unique_optional -----------------------------
template <class TokenT, class U, class D>
inline bool operator==(const TokenT& a,
                       const std_smart::unique_optional<U, D>& b) noexcept
{ return otn::internal::to_address(a) == b.get(); }

template <class TokenT, class U, class D>
inline bool operator==(const std_smart::unique_optional<U, D>& a,
                       const TokenT& b) noexcept
{ return b == a; }

template <class TokenT, class U, class D>
inline bool operator!=(const TokenT& a,
                       const std_smart::unique_optional<U, D>& b) noexcept
{ return !(a == b); }

template <class TokenT, class U, class D>
inline bool operator!=(const std_smart::unique_optional<U, D>& a,
                       const TokenT& b) noexcept
{ return !(a == b); }

template <class TokenT, class U, class D>
inline bool operator<(const TokenT& a,
                      const std_smart::unique_optional<U, D>& b) noexcept
{
    using E_T = typename TokenT::element_type;
    using E_U = typename std_smart::unique_optional<U, D>::element_type;
    using V   = typename std::common_type_t<E_T*, E_U*>;
    return std::less<V>()(otn::internal::to_address(a), b.get());
}

template <class TokenT, class U, class D>
inline bool operator<(const std_smart::unique_optional<U, D>& a,
                      const TokenT& b) noexcept
{
    using E_T = typename TokenT::element_type;
    using E_U = typename std_smart::unique_optional<U, D>::element_type;
    using V   = typename std::common_type_t<E_T*, E_U*>;
    return std::less<V>()(a.get(), otn::internal::to_address(b));
}

template <class TokenT, class U, class D>
inline bool operator>(const TokenT& a,
                      const std_smart::unique_optional<U, D>& b) noexcept
{ return b < a; }

template <class TokenT, class U, class D>
inline bool operator>(const std_smart::unique_optional<U, D>& a,
                      const TokenT& b) noexcept
{ return b < a; }

template <class TokenT, class U, class D>
inline bool operator<=(const TokenT& a,
                       const std_smart::unique_optional<U, D>& b) noexcept
{ return !(b < a); }

template <class TokenT, class U, class D>
inline bool operator<=(const std_smart::unique_optional<U, D>& a,
                       const TokenT& b) noexcept
{ return !(b < a); }

template <class TokenT, class U, class D>
inline bool operator>=(const TokenT& a,
                       const std_smart::unique_optional<U, D>& b) noexcept
{ return !(a < b); }

template <class TokenT, class U, class D>
inline bool operator>=(const std_smart::unique_optional<U, D>& a,
                       const TokenT& b) noexcept
{ return !(a < b); }
// ----- base::some <=> std_smart::unique_optional -----------------------------

// ----- base::some <=> std_smart::shared_optional -----------------------------
template <class TokenT, class U>
inline bool operator==(const TokenT& a,
                       const std_smart::shared_optional<U>& b) noexcept
{ return otn::internal::to_address(a) == b.get(); }

template <class TokenT, class U>
inline bool operator==(const std_smart::shared_optional<U>& a,
                       const TokenT& b) noexcept
{ return b == a; }

template <class TokenT, class U>
inline bool operator!=(const TokenT& a,
                       const std_smart::shared_optional<U>& b) noexcept
{ return !(a == b); }

template <class TokenT, class U>
inline bool operator!=(const std_smart::shared_optional<U>& a,
                       const TokenT& b) noexcept
{ return !(a == b); }

template <class TokenT, class U>
inline bool operator<(const TokenT& a,
                      const std_smart::shared_optional<U>& b) noexcept
{
    using E_T = typename TokenT::element_type;
    using E_U = typename std_smart::shared_optional<U>::element_type;
    using V   = typename std::common_type_t<E_T*, E_U*>;
    return std::less<V>()(otn::internal::to_address(a), b.get());
}

template <class TokenT, class U>
inline bool operator<(const std_smart::shared_optional<U>& a,
                      const TokenT& b) noexcept
{
    using E_T = typename TokenT::element_type;
    using E_U = typename std_smart::shared_optional<U>::element_type;
    using V   = typename std::common_type_t<E_T*, E_U*>;
    return std::less<V>()(a.get(), otn::internal::to_address(b));
}

template <class TokenT, class U>
inline bool operator>(const TokenT& a,
                      const std_smart::shared_optional<U>& b) noexcept
{ return b < a; }

template <class TokenT, class U>
inline bool operator>(const std_smart::shared_optional<U>& a,
                      const TokenT& b) noexcept
{ return b < a; }

template <class TokenT, class U>
inline bool operator<=(const TokenT& a,
                       const std_smart::shared_optional<U>& b) noexcept
{ return !(b < a); }

template <class TokenT, class U>
inline bool operator<=(const std_smart::shared_optional<U>& a,
                       const TokenT& b) noexcept
{ return !(b < a); }

template <class TokenT, class U>
inline bool operator>=(const TokenT& a,
                       const std_smart::shared_optional<U>& b) noexcept
{ return !(a < b); }

template <class TokenT, class U>
inline bool operator>=(const std_smart::shared_optional<U>& a,
                       const TokenT& b) noexcept
{ return !(a < b); }
// ----- base::some <=> std_smart::shared_optional -----------------------------

} // namespace base

} // namespace v1

} // namespace otn
