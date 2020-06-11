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

#include <otn/v1/access/functions.hpp>

#include <tuple>
#include <optional>

namespace otn
{

inline namespace v1
{

namespace internal
{

template <typename Object, typename ProxyList, std::size_t... Indices>
constexpr Object make_object(const ProxyList& proxy_list,
                             std::index_sequence<Indices...>)
{
    auto values = *proxy_list;
    using Values = decltype (values);
    using std::get;
    return Object{std::forward<std::tuple_element_t<Indices, Values>>(
                      get<Indices>(values))...};
}

} // namespace internal

template <typename Object, class ... Tokens>
constexpr std::optional<Object> try_make_object(Tokens&& ... tokens)
{
    if (auto locs = gain(std::forward<Tokens>(tokens)...))
        return internal::make_object<Object>(
            locs, std::make_index_sequence<sizeof... (Tokens)>{});

    return {};
}

} // namespace v1

} // namespace otn
