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

#include <otn/v1/base/detail/concepts.hpp>

#include <otn/v1/referrer/summaries.hpp>
#include <otn/v1/referrer/adaptor.hpp>

#include <otn/v1/element/traits.hpp>
#include <otn/v1/basis/traits.hpp>
#include <otn/v1/ownership/traits.hpp>
#include <otn/v1/multiplicity/traits.hpp>
#include <otn/v1/deleter/traits.hpp>

namespace otn
{

inline namespace v1
{

namespace referrer
{

template <class To, class Token>
struct adaptor<To, Token, std::enable_if_t<base::is_token_v<Token>>>
    : protected Token::accessor
{
protected:
    using referrer_summary =
        summaries::referrer<otn::traits::element_t<Token>,
                            spec::brief<otn::traits::basis_t<Token>,
                                        otn::traits::ownership_t<Token>,
                                        otn::traits::multiplicity_t<Token>,
                                        otn::traits::deleter_t<Token>>>;
    using referrer_type = typename referrer_summary::type;

public:
    static decltype(auto) adapt(const Token& from) noexcept
    {
        return adaptor<To, referrer_type>::adapt(
            adaptor{}.referrer(from));
    }

    static decltype(auto) adapt(Token && from) noexcept
    {
        return adaptor<To, referrer_type>::adapt(
            std::move(adaptor{}.referrer(from)));
    }
};

} // namespace referrer

} // namespace v1

} // namespace otn
