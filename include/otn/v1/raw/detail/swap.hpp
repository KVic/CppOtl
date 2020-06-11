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

#include <otn/v1/raw/detail/token.hpp>

namespace otn
{

inline namespace v1
{

namespace raw
{

// T - Type

// unified_optional
#ifdef __cpp_concepts
template <class T>
requires(unified_optional<T>::is_swappable)
#else
template <class T, OTN_CONCEPT_REQUIRES(unified_optional<T>::is_swappable)>
#endif
inline void swap(unified_optional<T>& a,
                 unified_optional<T>& b) noexcept(unified_optional<T>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T>
requires(!unified_optional<T>::is_swappable)
void swap(unified_optional<T>& a, unified_optional<T>& b) = delete;
#else
template <class T, OTN_CONCEPT_REQUIRES(!unified_optional<T>::is_swappable)>
void swap(unified_optional<T>& a, unified_optional<T>& b) = delete;
#endif

template <class T, class Y>
void swap(unified_optional<T>& a, unified_optional<Y>& b) = delete;

// unified_single
#ifdef __cpp_concepts
template <class T>
requires(unified_single<T>::is_swappable)
#else
template <class T, OTN_CONCEPT_REQUIRES(unified_single<T>::is_swappable)>
#endif
inline void swap(unified_single<T>& a,
                 unified_single<T>& b) noexcept(unified_single<T>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T>
requires(!unified_single<T>::is_swappable)
void swap(unified_single<T>& a, unified_single<T>& b) = delete;
#else
template <class T, OTN_CONCEPT_REQUIRES(!unified_single<T>::is_swappable)>
void swap(unified_single<T>& a, unified_single<T>& b) = delete;
#endif

template <class T, class Y>
void swap(unified_single<T>& a, unified_single<Y>& b) = delete;

// unique_optional
#ifdef __cpp_concepts
template <class T>
requires(unique_optional<T>::is_swappable)
#else
template <class T, OTN_CONCEPT_REQUIRES(unique_optional<T>::is_swappable)>
#endif
inline void swap(unique_optional<T>& a,
                 unique_optional<T>& b) noexcept(unique_optional<T>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T>
requires(!unique_optional<T>::is_swappable)
void swap(unique_optional<T>& a, unique_optional<T>& b) = delete;
#else
template <class T, OTN_CONCEPT_REQUIRES(!unique_optional<T>::is_swappable)>
void swap(unique_optional<T>& a, unique_optional<T>& b) = delete;
#endif

template <class T, class Y>
void swap(unique_optional<T>& a, unique_optional<Y>& b) = delete;

// unique_single
#ifdef __cpp_concepts
template <class T>
requires(unique_single<T>::is_swappable)
#else
template <class T, OTN_CONCEPT_REQUIRES(unique_single<T>::is_swappable)>
#endif
inline void swap(unique_single<T>& a,
                 unique_single<T>& b) noexcept(unique_single<T>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T>
requires(!unique_single<T>::is_swappable)
void swap(unique_single<T>& a, unique_single<T>& b) = delete;
#else
template <class T, OTN_CONCEPT_REQUIRES(!unique_single<T>::is_swappable)>
void swap(unique_single<T>& a, unique_single<T>& b) = delete;
#endif

template <class T, class Y>
void swap(unique_single<T>& a, unique_single<Y>& b) = delete;

// weak_optional
#ifdef __cpp_concepts
template <class T>
requires(weak_optional<T>::is_swappable)
#else
template <class T, OTN_CONCEPT_REQUIRES(weak_optional<T>::is_swappable)>
#endif
inline void swap(weak_optional<T>& a,
                 weak_optional<T>& b) noexcept(weak_optional<T>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T>
requires(!weak_optional<T>::is_swappable)
void swap(weak_optional<T>& a, weak_optional<T>& b) = delete;
#else
template <class T, OTN_CONCEPT_REQUIRES(!weak_optional<T>::is_swappable)>
void swap(weak_optional<T>& a, weak_optional<T>& b) = delete;
#endif

template <class T, class Y>
void swap(weak_optional<T>& a, weak_optional<Y>& b) = delete;

// weak_single
#ifdef __cpp_concepts
template <class T>
requires(weak_single<T>::is_swappable)
#else
template <class T, OTN_CONCEPT_REQUIRES(weak_single<T>::is_swappable)>
#endif
inline void swap(weak_single<T>& a,
                 weak_single<T>& b) noexcept(weak_single<T>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T>
requires(!weak_single<T>::is_swappable)
void swap(weak_single<T>& a, weak_single<T>& b) = delete;
#else
template <class T, OTN_CONCEPT_REQUIRES(!weak_single<T>::is_swappable)>
void swap(weak_single<T>& a, weak_single<T>& b) = delete;
#endif

template <class T, class Y>
void swap(weak_single<T>& a, weak_single<Y>& b) = delete;

} // namespace raw

} // namespace v1

} // namespace otn
