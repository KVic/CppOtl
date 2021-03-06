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

#include <otn/v1/referrer/rules.hpp>
#include <otn/v1/referrer/factory.hpp>
#include <otn/v1/safe/basis.hpp>
#include <otn/v1/std_smart/basis.hpp>
#include <otn/v1/std_smart/origin.hpp>

#include <otn/v1/ownership/names.hpp>
#include <otn/v1/spec/brief.hpp>

namespace otn
{

inline namespace v1
{

namespace referrer
{

// T - Type
// M - Multiplicity
// D - Deleter

template <class T, class M, class D>
struct specify<T, spec::brief<basis::safe, ownership::unified, M, D>, true>
{ using type = std_smart::shared_optional<T>; };

template <class T, class M, class D>
struct specify<T, spec::brief<basis::safe, ownership::unique, M, D>, true>
{ using type = std_smart::shared_optional<T>; };

template <class T, class M, class D>
struct specify<T, spec::brief<basis::safe, ownership::shared, M, D>, true>
{ using type = std_smart::shared_optional<T>; };

template <class T, class M, class D>
struct specify<T, spec::brief<basis::safe, ownership::weak, M, D>, true>
{ using type = std_smart::weak_optional<T>; };

} // namespace referrer

} // namespace v1

} // namespace otn
