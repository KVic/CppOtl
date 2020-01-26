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

#include <otn/v1/support/noexcept.hpp>

#include <utility>

namespace otn
{

inline namespace v1
{

namespace base
{

template <class Token, class Referrer, class = void>
struct factory
{
    static Token make(const Referrer& from) OTN_NOEXCEPT(
        noexcept(Token { from }))
    { return Token{from}; }

    static Token make(Referrer&& from) OTN_NOEXCEPT(
        noexcept(Token { std::move(from) }))
    { return Token{std::move(from)}; }
};

template <class Token, class Referrer>
inline Token make(Referrer&& from) OTN_NOEXCEPT(
    noexcept(factory<Token, otn::remove_cvref_t<Referrer>>::make(
                 std::forward<Referrer>(from))))
{
    return factory<Token, otn::remove_cvref_t<Referrer>>::make(
        std::forward<Referrer>(from));
}

} // namespace base

} // namespace v1

} // namespace otn
