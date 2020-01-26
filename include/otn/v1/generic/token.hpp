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

#include <otn/v1/generic/bind.hpp>
#include <otn/v1/ownership/names.hpp>
#include <otn/v1/multiplicity/names.hpp>

namespace otn
{

inline namespace v1
{

namespace generic
{

// T - Type

template <class T,
          class Basis, class Ownership, class Multiplicity,
          class Deleter = bind::deleter_t<T, Basis, Ownership>>
using token = bind::token_t<T, Basis, Ownership, Multiplicity, Deleter>;

template <class T, class Basis, class Multiplicity,
          class Deleter = bind::deleter_t<T, Basis, ownership::unified>>
using unified = token<T, Basis, ownership::unified, Multiplicity, Deleter>;

template <class T, class Basis, class Multiplicity,
          class Deleter = bind::deleter_t<T, Basis, ownership::unique>>
using unique = token<T, Basis, ownership::unique, Multiplicity, Deleter>;

template <class T, class Basis, class Multiplicity,
          class Deleter = bind::deleter_t<T, Basis, ownership::shared>>
using shared = token<T, Basis, ownership::shared, Multiplicity, Deleter>;

template <class T, class Basis, class Multiplicity,
          class Deleter = bind::deleter_t<T, Basis, ownership::weak>>
using weak = token<T, Basis, ownership::weak, Multiplicity, Deleter>;

template <class T, class Basis,
          class Deleter = bind::deleter_t<T, Basis, ownership::unified>>
using unified_optional = unified<T, Basis, multiplicity::optional, Deleter>;

template <class T, class Basis,
          class Deleter = bind::deleter_t<T, Basis, ownership::unique>>
using unique_optional = unique<T, Basis, multiplicity::optional, Deleter>;

template <class T, class Basis,
          class Deleter = bind::deleter_t<T, Basis, ownership::shared>>
using shared_optional = shared<T, Basis, multiplicity::optional, Deleter>;

template <class T, class Basis,
          class Deleter = bind::deleter_t<T, Basis, ownership::weak>>
using weak_optional = weak<T, Basis, multiplicity::optional, Deleter>;

template <class T, class Basis,
          class Deleter = bind::deleter_t<T, Basis, ownership::unified>>
using unified_single = unified<T, Basis, multiplicity::single, Deleter>;

template <class T, class Basis,
          class Deleter = bind::deleter_t<T, Basis, ownership::unique>>
using unique_single = unique<T, Basis, multiplicity::single, Deleter>;

template <class T, class Basis,
          class Deleter = bind::deleter_t<T, Basis, ownership::shared>>
using shared_single = shared<T, Basis, multiplicity::single, Deleter>;

template <class T, class Basis,
          class Deleter = bind::deleter_t<T, Basis, ownership::weak>>
using weak_single = weak<T, Basis, multiplicity::single, Deleter>;

} // namespace generic

} // namespace v1

} // namespace otn
