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

#include <otn/v1/conversion/rules.hpp>

#include <otn/v1/raw/basis.hpp>
#include <otn/v1/cpp_lang/basis.hpp>

#include <otn/v1/ownership/names.hpp>
#include <otn/v1/multiplicity/names.hpp>

namespace otn
{

inline namespace v1
{

namespace conversion
{

// T - Type
// B - Basis
// O - Ownership
// M - Multiplicity

// ----- copy construction & assignment ----------------------------------------
// raw::unified_any<T> <- cpp_lang::any_any<Y>
template <class TM,
          class YO, class YM>
struct
property<copy_construction,
         basis::raw, ownership::unified, TM,
         basis::cpp_lang, YO, YM> : implicit_enabled {};

// raw::weak_any<T> <- cpp_lang::unified_unknown<Y>
template <class TM>
struct
property<copy_construction,
         basis::raw, ownership::weak, TM,
         basis::cpp_lang, ownership::unified, multiplicity::unknown> : explicit_enabled {};
// ----- copy construction & assignment ----------------------------------------

// ----- copy conversion -------------------------------------------------------
// cpp_lang::unified_unknown<Y> <- raw::any_any<T>
template <class TO, class TM>
struct
property<copy_conversion,
         basis::raw, TO, TM,
         basis::cpp_lang, ownership::unified, multiplicity::unknown> : explicit_enabled {};

// cpp_lang::unified_optional<Y> <- raw::any_any<T>
template <class TO, class TM>
struct
property<copy_conversion,
         basis::raw, TO, TM,
         basis::cpp_lang, ownership::unified, multiplicity::optional> : implicit_enabled {};
// ----- copy conversion -------------------------------------------------------

// ----- move construction & assignment ----------------------------------------
// raw::unified_any<T> <- cpp_lang::unified_any<Y>
template <class TM,
          class YM>
struct
property<move_construction,
         basis::raw, ownership::unified, TM,
         basis::cpp_lang, ownership::unified, YM> : implicit_enabled {};

// raw::weak_any<T> <- cpp_lang::unified_unknown<Y>
template <class TM>
struct
property<move_construction,
         basis::raw, ownership::weak, TM,
         basis::cpp_lang, ownership::unified, multiplicity::unknown> : explicit_enabled {};
// ----- move construction & assignment ----------------------------------------

// ----- move conversion -------------------------------------------------------
// cpp_lang::unified_unknown<Y> <- raw::some_any<T>
template <class TM>
struct
property<move_conversion,
         basis::raw, ownership::unified, TM,
         basis::cpp_lang, ownership::unified, multiplicity::unknown> : explicit_enabled {};

template <class TM>
struct
property<move_conversion,
         basis::raw, ownership::weak, TM,
         basis::cpp_lang, ownership::unified, multiplicity::unknown> : explicit_enabled {};

// cpp_lang::unified_optional<Y> <- raw::some_any<T>
template <class TM>
struct
property<move_conversion,
         basis::raw, ownership::unified, TM,
         basis::cpp_lang, ownership::unified, multiplicity::optional> : implicit_enabled {};

template <class TM>
struct
property<move_conversion,
         basis::raw, ownership::weak, TM,
         basis::cpp_lang, ownership::unified, multiplicity::optional> : implicit_enabled {};
// ----- move conversion -------------------------------------------------------

} // namespace conversion

} // inline namespace v1

} // namespace otn
