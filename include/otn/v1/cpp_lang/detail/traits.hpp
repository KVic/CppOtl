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

#include <otn/v1/element/traits.hpp>
#include <otn/v1/basis/traits.hpp>
#include <otn/v1/ownership/traits.hpp>
#include <otn/v1/multiplicity/traits.hpp>
#include <otn/v1/lifetime/traits.hpp>
#include <otn/v1/lifetime/detector.hpp>

#include <otn/v1/cpp_lang/origin.hpp>
#include <otn/v1/cpp_lang/basis.hpp>

namespace otn
{

inline namespace v1
{

namespace traits
{

// T - Type

// unified_unknown
template <class T>
struct element<cpp_lang::unified_unknown<T>>
{ using type = T; };

template <class T>
struct basis<cpp_lang::unified_unknown<T>>
{ using type = otn::basis::cpp_lang; };

template <class T>
struct ownership<cpp_lang::unified_unknown<T>>
{ using type = otn::ownership::unified; };

template <class T>
struct multiplicity<cpp_lang::unified_unknown<T>>
{ using type = otn::multiplicity::unknown; };

// unified_optional
template <class T>
struct element<cpp_lang::unified_optional<T>>
{ using type = T; };

template <class T>
struct basis<cpp_lang::unified_optional<T>>
{ using type = otn::basis::cpp_lang; };

template <class T>
struct ownership<cpp_lang::unified_optional<T>>
{ using type = otn::ownership::unified; };

template <class T>
struct multiplicity<cpp_lang::unified_optional<T>>
{ using type = otn::multiplicity::optional; };

namespace lifetime
{

template <class Token>
struct role<Token,
            std::enable_if_t<basis_is_v<Token, otn::basis::cpp_lang>>>
{
    static constexpr otn::lifetime::role value =
        otn::lifetime::detect_role<deleter_t<Token>>;
};

} // namespace lifetime

} // namespace traits

} // inline namespace v1

} // namespace otn
