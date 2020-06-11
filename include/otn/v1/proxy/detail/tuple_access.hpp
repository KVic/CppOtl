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

#include <otn/v1/proxy/detail/list.hpp>

namespace otn
{

inline namespace v1
{

namespace proxy
{

// values
template <std::size_t Index, class ... Tokens>
constexpr decltype (auto)
get(values<list, Tokens...>&proxy_values) noexcept
{
    return proxy_values.template get<Index>();
}

template <std::size_t Index, class ... Tokens>
constexpr decltype (auto)
get(values<list, Tokens...>&& proxy_values) noexcept
{
    return proxy_values.template get<Index>();
}

template <std::size_t Index, class ... Tokens>
constexpr decltype (auto)
get(const values<list, Tokens...>&proxy_values) noexcept
{
    return proxy_values.template get<Index>();
}

// list
template <std::size_t Index, class ... Tokens>
constexpr decltype (auto)
get(list<Tokens...>&proxy_list) noexcept
{
    return proxy_list.template get<Index>();
}

template <std::size_t Index, class ... Tokens>
constexpr decltype (auto)
get(list<Tokens...>&& proxy_list) noexcept
{
    return proxy_list.template get<Index>();
}

template <std::size_t Index, class ... Tokens>
constexpr decltype (auto)
get(const list<Tokens...>&proxy_list) noexcept
{
    return proxy_list.template get<Index>();
}

} // namespace proxy

} // namespace v1

} // namespace otn

namespace std
{

// otn::proxy::values
template <class ... Tokens>
struct tuple_size<otn::proxy::values<otn::proxy::list, Tokens...>>
    : std::integral_constant<std::size_t, sizeof...(Tokens)> {};

template <std::size_t Index, class ... Tokens>
struct tuple_element<Index, otn::proxy::values<otn::proxy::list, Tokens...>>
{
    using proxy_values = otn::proxy::values<otn::proxy::list, Tokens...>;
    static_assert(Index < tuple_size<proxy_values>::value,
                  "proxy::values index is in range");
    using type = decltype(declval<proxy_values&>().template get<Index>());
};

template <std::size_t Index, class ... Tokens>
struct tuple_element<Index, const otn::proxy::values<otn::proxy::list, Tokens...>>
{
    using proxy_values = otn::proxy::values<otn::proxy::list, Tokens...>;
    static_assert(Index < tuple_size<proxy_values>::value,
                  "proxy::values index is in range");
    using type = decltype(declval<const proxy_values&>().template get<Index>());
};

// otn::proxy::list
template <class ... Tokens>
struct tuple_size<otn::proxy::list<Tokens...>>
    : std::integral_constant<std::size_t, sizeof...(Tokens)> {};

template <std::size_t Index, class ... Tokens>
struct tuple_element<Index, otn::proxy::list<Tokens...>>
{
    using proxy_list = otn::proxy::list<Tokens...>;
    static_assert(Index < tuple_size<proxy_list>::value,
                  "proxy::list index is in range");
    using type = decltype(declval<proxy_list&>().template get<Index>());
};

template <std::size_t Index, class ... Tokens>
struct tuple_element<Index, const otn::proxy::list<Tokens...>>
{
    using proxy_list = otn::proxy::list<Tokens...>;
    static_assert(Index < tuple_size<proxy_list>::value,
                  "proxy::list index is in range");
    using type = decltype(declval<const proxy_list&>().template get<Index>());
};

} // namespace std
