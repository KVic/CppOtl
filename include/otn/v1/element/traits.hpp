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

#include <otn/v1/support/type_traits.hpp>

namespace otn
{

inline namespace v1
{

namespace traits
{

template <class Token, class = void>
struct element
{ using type = void; };

template <class Token>
using element_t = typename element<otn::remove_cvref_t<Token>>::type;

} // namespace traits

template <class Token, class Element>
inline constexpr bool element_is_v =
    std::is_same_v<traits::element_t<Token>, Element>;

template <class From, class To>
static constexpr bool is_elements_convertible =
    std::is_convertible_v<std::remove_reference_t<From>*,
                          std::remove_reference_t<To>*>;

template <class This, class With>
static constexpr bool is_elements_incompatible =
    !is_elements_convertible<std::remove_const_t<With>,
                             std::remove_const_t<This>>;

// Const incorrectness conversion: 'const With* -> This*'.
template <class This, class With>
static constexpr bool is_elements_const_incorrect =
    std::is_const_v<With>
    && !std::is_const_v<This>
    && is_elements_convertible<std::remove_const_t<With>,
                               std::remove_const_t<This>>;

} // namespace v1

} // namespace otn
