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

#include <otn/v1/multiplicity/names.hpp>

#include <otn/v1/support/type_traits.hpp>

namespace otn
{

inline namespace v1
{

namespace multiplicity
{

template <class Multiplicity>
inline constexpr bool is_optional_v = std::is_same_v<Multiplicity, optional>;
template <class Multiplicity>
inline constexpr bool is_single_v = std::is_same_v<Multiplicity, single>;

} // namespace multiplicity

namespace traits
{

template <class Token, class = void>
struct multiplicity
{ using type = otn::multiplicity::unknown; };

template <class Token>
using multiplicity_t = typename multiplicity<otn::remove_cvref_t<Token>>::type;

} // namespace traits

template <class Token, class Multiplicity>
inline constexpr bool multiplicity_is_v =
    std::is_same_v<traits::multiplicity_t<Token>, Multiplicity>;

template <class Token>
inline constexpr bool is_optional_v =
    otn::multiplicity::is_optional_v<traits::multiplicity_t<Token>>;

template <class Token>
inline constexpr bool is_single_v =
    otn::multiplicity::is_single_v<traits::multiplicity_t<Token>>;

} // namespace v1

} // namespace otn
