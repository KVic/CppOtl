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

#include <otn/v1/referrer/adaptor.hpp>

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
    using typename Token::accessor::referrer_type;
    using referrer_adaptor = adaptor<To, referrer_type>;

public:
    static constexpr bool is_copy_constructible =
        referrer_adaptor::is_copy_constructible;
    static constexpr bool is_move_constructible =
        referrer_adaptor::is_move_constructible;
    static constexpr bool is_copy_assignable =
        referrer_adaptor::is_copy_assignable;
    static constexpr bool is_move_assignable =
        referrer_adaptor::is_move_assignable;

    static constexpr bool is_nothrow_copy_constructible =
        referrer_adaptor::is_nothrow_copy_constructible;
    static constexpr bool is_nothrow_move_constructible =
        referrer_adaptor::is_nothrow_move_constructible;

    static To
    adapt(const Token& from) noexcept(is_nothrow_copy_constructible)
    { return referrer_adaptor::adapt(adaptor{}.referrer(from)); }

    static To
    adapt(Token&& from) noexcept(is_nothrow_move_constructible)
    { return referrer_adaptor::adapt(std::move(adaptor{}.referrer(from))); }
};

} // namespace referrer

} // namespace v1

} // namespace otn
