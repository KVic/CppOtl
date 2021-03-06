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

#include <otn/v1/generic/token.hpp>

#include <otn/v1/safe/detail/generic.hpp>

namespace otn
{

inline namespace v1
{

namespace safe
{

// T - Type

template <class T,
          class Ownership = ownership::unified,
          class Multiplicity = multiplicity::optional,
          class Deleter = generic::bind::deleter_t<T, basis::safe, Ownership>>
using token = generic::token<T, basis::safe, Ownership, Multiplicity, Deleter>;

template <class T>
using unified = unified_single<T>;

template <class T>
using unique = unique_single<T>;

template <class T>
using shared = shared_single<T>;

} // namespace safe

} // namespace v1

} // namespace otn
