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

#include <otn/v1/referrer/adaptor_traits.hpp>

#include <utility>

namespace otn
{

inline namespace v1
{

namespace referrer
{

// cpp_lang::divided_observer <- std_smart::divided_observer adaptor
template <class To, class From>
struct adaptor_cpp_lang_observer_std_smart_observer
    : traits_divided_any_divided_observer<otn::traits::element_t<To>,
                                          otn::traits::element_t<From>>
{
    static To adapt(const From& from) noexcept
    { return To{from.lock().get()}; }

    static To adapt(From&& from) noexcept
    {
        From temp{std::move(from)};
        return To{temp.lock().get()};
    }
};

} // namespace referrer

} // namespace v1

} // namespace otn
