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
#include <otn/v1/layout/traits.hpp>
#include <otn/v1/base/traits.hpp>
#include <otn/v1/referrer/traits.hpp>

#include <otn/v1/base/rules.hpp>
#include <otn/v1/referrer/summaries.hpp>
#include <otn/v1/lifetime/rules.hpp>
#include <otn/v1/base/detail/concepts.hpp>

namespace otn
{

inline namespace v1
{

namespace traits
{

template <class Token>
struct element<Token, std::enable_if_t<base::is_token_v<Token>>>
{ using type = typename Token::element_type; };

template <class Token>
struct basis<Token, std::enable_if_t<base::is_token_v<Token>>>
{ using type = typename Token::brief_spec::basis; };

template <class Token>
struct ownership<Token, std::enable_if_t<base::is_token_v<Token>>>
{ using type = typename Token::brief_spec::ownership; };

template <class Token>
struct multiplicity<Token, std::enable_if_t<base::is_token_v<Token>>>
{ using type = typename Token::brief_spec::multiplicity; };

template <class Token>
struct deleter<Token, std::enable_if_t<base::is_token_v<Token>>>
{ using type = typename Token::brief_spec::deleter; };

namespace lifetime
{

template <class Token>
struct role<Token, std::enable_if_t<base::is_token_v<Token>>>
{
    static constexpr otn::lifetime::role value =
        otn::lifetime::specify_role<basis_t<Token>,
                                    ownership_t<Token>,
                                    deleter_t<Token>>;
};

} // namespace lifetime

template <class Token>
struct layout<Token, std::enable_if_t<base::is_token_v<Token>>>
{
protected:
    using referrer_summary = summaries::referrer<typename Token::element_type,
                                                 typename Token::brief_spec>;
    using referrer_type = typename referrer_summary::type;

public:
    using type = otn::traits::layout_t<referrer_type>;
};

} // namespace traits

template <class Token>
struct is_trackable<Token, std::enable_if_t<base::is_token_v<Token>>>
    : std::bool_constant<
          referrer::enable_tracking<traits::basis_t<Token>,
                                    traits::ownership_t<Token>>> {};
template <class Token>
struct is_dereferenceable<Token, std::enable_if_t<base::is_token_v<Token>>>
    : std::bool_constant<
          base::enable_dereferencing<traits::basis_t<Token>,
                                     traits::ownership_t<Token>>> {};

template <class Token>
struct is_direct_accessible<Token, std::enable_if_t<base::is_token_v<Token>>>
    : std::bool_constant<
          base::enable_direct_access<traits::basis_t<Token>,
                                     traits::ownership_t<Token>>> {};

} // namespace v1

} // namespace otn
