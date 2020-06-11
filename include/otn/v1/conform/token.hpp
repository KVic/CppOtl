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
#include <otn/v1/multiplicity/traits.hpp>
#include <otn/v1/deleter/traits.hpp>
#include <otn/v1/lifetime/traits.hpp>
#include <otn/v1/generic/token.hpp>
#include <otn/v1/support/concept.hpp>

#include <utility>

namespace otn
{

inline namespace v1
{

namespace conform
{

template <class Token, class = void>
struct specify_weak
{
    using type = otn::generic::weak<traits::element_t<Token>,
                                    traits::basis_t<Token>,
                                    traits::multiplicity_t<Token>,
                                    traits::deleter_t<Token>>;
};

template <class Token>
using weak_t = typename specify_weak<Token>::type;

#ifdef __cpp_concepts
template <class Token>
requires(is_token_v<Token>)
#else
template <class Token,
          OTN_CONCEPT_REQUIRES(is_token_v<Token>)>
#endif
inline
auto weak(Token&& token)
{
    return weak_t<otn::remove_cvref_t<Token>>{std::forward<Token>(token)};
}

} // namespace conform

} // namespace v1

} // namespace otn
