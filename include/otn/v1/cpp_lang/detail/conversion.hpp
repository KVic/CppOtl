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
// cpp_lang::unified_unknown<T> <- cpp_lang::some_some<Y>
template <>
struct
property<copy_construction,
         basis::cpp_lang, ownership::unified, multiplicity::unknown,
         basis::cpp_lang, ownership::unified, multiplicity::unknown> : implicit_enabled {};

template <>
struct
property<copy_construction,
         basis::cpp_lang, ownership::unified, multiplicity::unknown,
         basis::cpp_lang, ownership::unified, multiplicity::optional> : implicit_enabled {};

template <class YM>
struct
property<copy_construction,
         basis::cpp_lang, ownership::unified, multiplicity::unknown,
         basis::cpp_lang, ownership::unique, YM> : explicit_enabled {};

// cpp_lang::unified_optional<T> <- cpp_lang::some_some<Y>
template <>
struct
property<copy_construction,
         basis::cpp_lang, ownership::unified, multiplicity::optional,
         basis::cpp_lang, ownership::unified, multiplicity::unknown> : implicit_enabled {};

template <>
struct
property<copy_construction,
         basis::cpp_lang, ownership::unified, multiplicity::optional,
         basis::cpp_lang, ownership::unified, multiplicity::optional> : implicit_enabled {};

template <class YM>
struct
property<copy_construction,
         basis::cpp_lang, ownership::unified, multiplicity::optional,
         basis::cpp_lang, ownership::unique, YM> : explicit_enabled {};
// ----- copy construction & assignment ----------------------------------------

// ----- move construction & assignment ----------------------------------------
// cpp_lang::unified_unknown<T> <- cpp_lang::unified_some<Y>
template <>
struct
property<move_construction,
         basis::cpp_lang, ownership::unified, multiplicity::unknown,
         basis::cpp_lang, ownership::unified, multiplicity::unknown> : implicit_enabled {};

template <>
struct
property<move_construction,
         basis::cpp_lang, ownership::unified, multiplicity::unknown,
         basis::cpp_lang, ownership::unified, multiplicity::optional> : implicit_enabled {};

// cpp_lang::unified_optional<T> <- cpp_lang::unified_some<Y>
template <>
struct
property<move_construction,
         basis::cpp_lang, ownership::unified, multiplicity::optional,
         basis::cpp_lang, ownership::unified, multiplicity::unknown> : implicit_enabled {};

template <>
struct
property<move_construction,
         basis::cpp_lang, ownership::unified, multiplicity::optional,
         basis::cpp_lang, ownership::unified, multiplicity::optional> : implicit_enabled {};
// ----- move construction & assignment ----------------------------------------

} // namespace conversion

} // inline namespace v1

} // namespace otn
