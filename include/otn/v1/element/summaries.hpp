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

#include <type_traits>

namespace otn
{

inline namespace v1
{

namespace summaries
{

// T - Type

template <class From, class To>
static constexpr bool is_convertible_elements =
    std::is_convertible_v<std::remove_reference_t<From>*,
                          std::remove_reference_t<To>*>;

template <class T>
struct element
{
    using type = T;

    template <class Element>
    static constexpr bool is_convertible_from =
        is_convertible_elements<Element, type>;

    template <class Element>
    static constexpr bool is_convertible_to =
        is_convertible_elements<type, Element>;

    template <class Element>
    static constexpr bool is_incompatible_with =
        !is_convertible_elements<std::remove_const_t<Element>,
                                 std::remove_const_t<type>>;

    // Const incorrectness conversion: 'const Element* -> type*'.
    template <class Element>
    static constexpr bool is_const_incorrect_with =
        std::is_const_v<Element>
        && !std::is_const_v<type>
        && is_convertible_elements<std::remove_const_t<Element>,
                                   std::remove_const_t<type>>;
};

} // namespace summaries

} // namespace v1

} // namespace otn
