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

#include <otn/v1/proxy/factory.hpp>

#include <otn/v1/support/concept.hpp>
#include <otn/v1/support/to_value.hpp>

#include <otn/v1/multiplicity/traits.hpp>

#include <tuple>

namespace otn
{

inline namespace v1
{

namespace proxy
{

namespace internal
{

template <class Token>
constexpr std::enable_if_t<is_single_v<Token>, bool>
is_true(const Token&) noexcept { return true; }

template <class Token>
constexpr std::enable_if_t<!is_single_v<Token>, bool>
is_true(const Token& value) noexcept { return static_cast<bool>(value); }

template <class ... Booleans, std::size_t ... Indices>
constexpr bool is_all_true(const std::tuple<Booleans...>& values,
                           std::index_sequence<Indices...>) noexcept
{ return(is_true(std::get<Indices>(values)) && ...); }

} // namespace internal

template <class ... Tokens>
class list
{
protected:
    static constexpr std::size_t proxies_count = sizeof... (Tokens);
    static_assert(proxies_count > 0, "proxy::list is not empty");

    using proxies_type =
        std::tuple<decltype(proxy::make(std::declval<Tokens>()))...>;

    template <std::size_t Index>
    using content_type =
        typename std::pointer_traits<
            otn::remove_cvref_t<
                std::tuple_element_t<Index, proxies_type>>>::element_type&;

public:
    explicit list(proxies_type proxies) noexcept
        : m_proxies{std::move(proxies)}
    {}

    [[nodiscard]]
    operator bool() const & noexcept
    {
        return internal::is_all_true(
            m_proxies, std::make_index_sequence<proxies_count>{});
    }

    operator bool() const&& = delete;

    template <std::size_t Index>
    content_type<Index> get() const & noexcept
    { return otn::internal::to_value(std::get<Index>(m_proxies)); }

    template <std::size_t Index>
    content_type<Index> get() const&& = delete;

    OTN_CONCEPT_REQUIRES_(proxies_count == 1)
    content_type<0> operator*() const & noexcept
    { return get<0>(); }

    OTN_CONCEPT_REQUIRES_(proxies_count > 1)
    content_type<0> operator*() = delete;
    content_type<0> operator*() const&& = delete;

private:
    const proxies_type m_proxies;
};

template <std::size_t Index, typename ... Tokens>
constexpr std::tuple_element_t<Index, list<Tokens...>>
get(const list<Tokens...>& proxy_list) noexcept
{ return proxy_list.template get<Index>(); }

template <std::size_t Index, typename ... Tokens>
constexpr std::tuple_element_t<Index, list<Tokens...>>
get(list<Tokens...>&& proxy_list) = delete;

} // namespace proxy

} // namespace v1

} // namespace otn

namespace std
{

template <class ... Tokens>
struct tuple_size<otn::proxy::list<Tokens...>>
    : std::integral_constant<std::size_t, sizeof...(Tokens)> {};

template <std::size_t Index, class ... Tokens>
struct tuple_element<Index, otn::proxy::list<Tokens...>>
{
    using proxy_list = otn::proxy::list<Tokens...>;
    static_assert(Index < tuple_size<proxy_list>::value,
                  "proxy::list index is in range");
    using type = decltype(declval<const proxy_list&>().template get<Index>());
};

template <std::size_t Index, class ... Tokens>
struct tuple_element<Index, const otn::proxy::list<Tokens...>>
{
    using proxy_list = otn::proxy::list<Tokens...>;
    using type       =
        decltype(as_const(declval<const proxy_list&>().template get<Index>()));
};

} // namespace std
