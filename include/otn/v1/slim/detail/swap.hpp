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

#include <otn/v1/slim/detail/token.hpp>

namespace otn
{

inline namespace v1
{

namespace slim
{

// T - Type
// D - Deleter

// unique_optional
#ifdef __cpp_concepts
template <class T, class D>
requires(unique_optional<T, D>::is_swappable)
#else
template <class T, class D,
          OTN_CONCEPT_REQUIRES(unique_optional<T, D>::is_swappable)>
#endif
inline void swap(unique_optional<T, D>& a,
                 unique_optional<T, D>& b) noexcept(unique_optional<T, D>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T, class D>
requires(!unique_optional<T, D>::is_swappable)
void swap(unique_optional<T, D>& a, unique_optional<T, D>& b) = delete;
#else
template <class T, class D,
          OTN_CONCEPT_REQUIRES(!unique_optional<T, D>::is_swappable)>
void swap(unique_optional<T, D>& a, unique_optional<T, D>& b) = delete;
#endif

template <class T, class DT, class Y, class DY>
void swap(unique_optional<T, DT>& a, unique_optional<Y, DY>& b) = delete;

// unique_single
#ifdef __cpp_concepts
template <class T, class D>
requires(unique_single<T, D>::is_swappable)
#else
template <class T, class D,
          OTN_CONCEPT_REQUIRES(unique_single<T, D>::is_swappable)>
#endif
inline void swap(unique_single<T, D>& a,
                 unique_single<T, D>& b) noexcept(unique_single<T, D>::is_nothrow_swappable)
{ a.swap(b); }

#ifdef __cpp_concepts
template <class T, class D>
requires(!unique_single<T, D>::is_swappable)
void swap(unique_single<T, D>& a, unique_single<T, D>& b) = delete;
#else
template <class T, class D,
          OTN_CONCEPT_REQUIRES(!unique_single<T, D>::is_swappable)>
void swap(unique_single<T, D>& a, unique_single<T, D>& b) = delete;
#endif

template <class T, class DT, class Y, class DY>
void swap(unique_single<T, DT>& a, unique_single<Y, DY>& b) = delete;

} // namespace slim

} // namespace v1

} // namespace otn
