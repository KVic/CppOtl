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

#include <otn/v1/ownership/names.hpp>
#include <otn/v1/generic/bind.hpp>

#include <otn/v1/safe/detail/token.hpp>

namespace otn
{

inline namespace v1
{

namespace generic
{

namespace bind
{

// T - Type
// D - Deleter

template <class T, class D>
struct token<T, basis::safe, otn::ownership::unified, otn::multiplicity::optional, D>
{ using type = otn::safe::unified_optional<T>; };

template <class T, class D>
struct token<T, basis::safe, otn::ownership::unified, otn::multiplicity::single, D>
{ using type = otn::safe::unified_single<T>; };

template <class T, class D>
struct token<T, basis::safe, otn::ownership::unique, otn::multiplicity::optional, D>
{ using type = otn::safe::unique_optional<T>; };

template <class T, class D>
struct token<T, basis::safe, otn::ownership::unique, otn::multiplicity::single, D>
{ using type = otn::safe::unique_single<T>; };

template <class T, class D>
struct token<T, basis::safe, otn::ownership::shared, otn::multiplicity::optional, D>
{ using type = otn::safe::shared_optional<T>; };

template <class T, class D>
struct token<T, basis::safe, otn::ownership::shared, otn::multiplicity::single, D>
{ using type = otn::safe::shared_single<T>; };

template <class T, class D>
struct token<T, basis::safe, otn::ownership::weak, otn::multiplicity::optional, D>
{ using type = otn::safe::weak_optional<T>; };

} // namespace bind

} // namespace generic

} // namespace v1

} // namespace otn
