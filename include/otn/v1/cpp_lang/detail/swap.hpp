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

#include <otn/v1/support/concept.hpp>

namespace otn
{

inline namespace v1
{

namespace cpp_lang
{

// T - Type

// unified_optional
template <class T>
inline void swap(unified_optional<T>& a,
                 unified_optional<T>& b) noexcept
{ a.swap(b); }

// thin_optional
#ifdef __cpp_concepts
template <class T>
requires(thin_optional<T>::is_swappable)
#else
template <class T, OTN_CONCEPT_REQUIRES(thin_optional<T>::is_swappable)>
#endif
inline void swap(thin_optional<T>& a,
                 thin_optional<T>& b) noexcept(thin_optional<T>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T>
requires(!thin_optional<T>::is_swappable)
void swap(thin_optional<T>& a, thin_optional<T>& b) = delete;
#else
template <class T, OTN_CONCEPT_REQUIRES(!thin_optional<T>::is_swappable)>
void swap(thin_optional<T>& a, thin_optional<T>& b) = delete;
#endif

template <class T, class Y>
void swap(thin_optional<T>& a, thin_optional<Y>& b) = delete;

// thin_single
#ifdef __cpp_concepts
template <class T>
requires(thin_single<T>::is_swappable)
#else
template <class T, OTN_CONCEPT_REQUIRES(thin_single<T>::is_swappable)>
#endif
inline void swap(thin_single<T>& a,
                 thin_single<T>& b) noexcept(thin_single<T>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T>
requires(!thin_single<T>::is_swappable)
void swap(thin_single<T>& a, thin_single<T>& b) = delete;
#else
template <class T, OTN_CONCEPT_REQUIRES(!thin_single<T>::is_swappable)>
void swap(thin_single<T>& a, thin_single<T>& b) = delete;
#endif

template <class T, class Y>
void swap(thin_single<T>& a, thin_single<Y>& b) = delete;

} // namespace cpp_lang

} // namespace v1

} // namespace otn
