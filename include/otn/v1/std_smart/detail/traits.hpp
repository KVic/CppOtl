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
#include <otn/v1/deleter/traits.hpp>
#include <otn/v1/lifetime/traits.hpp>
#include <otn/v1/lifetime/detector.hpp>
#include <otn/v1/referrer/traits.hpp>
#include <otn/v1/base/traits.hpp>

#include <otn/v1/std_smart/origin.hpp>
#include <otn/v1/std_smart/basis.hpp>

namespace otn
{

inline namespace v1
{

// T - Type
// D - Deleter

namespace traits
{

// unique_optional
template <class T, class D>
struct element<std_smart::unique_optional<T, D>>
{ using type = typename std_smart::unique_optional<T, D>::element_type; };

template <class T, class D>
struct basis<std_smart::unique_optional<T, D>>
{ using type = otn::basis::std_smart; };

template <class T, class D>
struct ownership<std_smart::unique_optional<T, D>>
{ using type = otn::ownership::unique; };

template <class T, class D>
struct multiplicity<std_smart::unique_optional<T, D>>
{ using type = otn::multiplicity::optional; };

template <class T, class D>
struct deleter<std_smart::unique_optional<T, D>>
{ using type = D; };

// shared_optional
template <class T>
struct element<std_smart::shared_optional<T>>
{ using type = typename std_smart::shared_optional<T>::element_type; };

template <class T>
struct basis<std_smart::shared_optional<T>>
{ using type = otn::basis::std_smart; };

template <class T>
struct ownership<std_smart::shared_optional<T>>
{ using type = otn::ownership::shared; };

template <class T>
struct multiplicity<std_smart::shared_optional<T>>
{ using type = otn::multiplicity::optional; };

template <class T>
struct deleter<std_smart::shared_optional<T>>
{ using type = otn::deleter::by_default; };

// weak_optional
template <class T>
struct element<std_smart::weak_optional<T>>
{ using type = typename std_smart::weak_optional<T>::element_type; };

template <class T>
struct basis<std_smart::weak_optional<T>>
{ using type = otn::basis::std_smart; };

template <class T>
struct ownership<std_smart::weak_optional<T>>
{ using type = otn::ownership::weak; };

template <class T>
struct multiplicity<std_smart::weak_optional<T>>
{ using type = otn::multiplicity::optional; };

namespace lifetime
{

template <class Token>
struct role<Token,
            std::enable_if_t<basis_is_v<Token, otn::basis::std_smart>>>
{
    static constexpr otn::lifetime::role value =
        otn::lifetime::detect_role<deleter_t<Token>>;
};

} // namespace lifetime

} // namespace traits

// shared_optional
template <class T>
struct is_trackable<std_smart::shared_optional<T>>
    : std::true_type {};

// weak_optional
template <class T>
struct is_dereferenceable<std_smart::weak_optional<T>>
    : std::false_type {};

template <class T>
struct is_direct_accessible<std_smart::weak_optional<T>>
    : std::false_type {};

template <class T>
struct is_trackable<std_smart::weak_optional<T>>
    : std::true_type {};

} // inline namespace v1

} // namespace otn
