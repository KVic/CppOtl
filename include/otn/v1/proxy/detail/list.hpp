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

template <template <class ... Tokens> class List, class ... Tokens>
class values
{
protected:
    using proxies_type =
        std::tuple<decltype(proxy::make(std::declval<Tokens>()))...>;

    template <std::size_t Index>
    using content_type =
        typename std::pointer_traits<
            otn::remove_cvref_t<
                std::tuple_element_t<Index, proxies_type>>>::element_type;

public:
    template <std::size_t Index>
    content_type<Index>&
    get() noexcept
    {
        return otn::internal::to_value(
            static_cast<List<Tokens...>&>(*this).template get<Index>());
    }

    template <std::size_t Index>
    const content_type<Index>&
    get() const noexcept
    {
        return otn::internal::to_value(
            static_cast<const List<Tokens...>&>(*this).template get<Index>());
    }
};

template <class ... Tokens>
class list : public values<list, Tokens...>
{
private:
    static constexpr std::size_t proxies_count = sizeof... (Tokens);
    static_assert(proxies_count > 0, "proxy list is not empty");

    using values = proxy::values<list, Tokens...>;
    using typename values::proxies_type;

public:
    explicit list(Tokens ... tokens) noexcept
        // TODO: Optimize for several tokens.
        : m_proxies{proxy::make(std::forward<Tokens>(tokens))...}
    {}

    [[nodiscard]]
    operator bool() const & noexcept
    {
        return internal::is_all_true(
            (*this).m_proxies,
            std::make_index_sequence<proxies_count>{});
    }

    operator bool() && = delete;

    template <std::size_t Index>
    std::tuple_element_t<Index, proxies_type>&
    get() noexcept
    { return std::get<Index>((*this).m_proxies); }

    template <std::size_t Index>
    const std::remove_reference_t<std::tuple_element_t<Index, proxies_type>>&
    get() const noexcept
    { return std::get<Index>((*this).m_proxies); }

#ifdef __cpp_concepts
    template <class Token>
    requires(proxies_count == 1)
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(proxies_count == 1)>
#endif
    operator Token() const noexcept { return Token{get<0>()}; }

#ifdef __cpp_concepts
    decltype (auto) operator*() noexcept
    requires(proxies_count == 1)
#else
    OTN_CONCEPT_REQUIRES_(proxies_count == 1)
    decltype (auto) operator*() noexcept
#endif
    { return values::template get<0>(); }

#ifdef __cpp_concepts
    decltype (auto) operator*() const noexcept
    requires(proxies_count == 1)
#else
    OTN_CONCEPT_REQUIRES_(proxies_count == 1)
    decltype (auto) operator*() const noexcept
#endif
    { return values::template get<0>(); }

#ifdef __cpp_concepts
    values& operator*() noexcept
    requires(proxies_count > 1)
#else
    OTN_CONCEPT_REQUIRES_(proxies_count > 1)
    values & operator*() noexcept
#endif
    { return *this; }

#ifdef __cpp_concepts
    const values& operator*() const noexcept
    requires(proxies_count > 1)
#else
    OTN_CONCEPT_REQUIRES_(proxies_count > 1)
    const values& operator*() const noexcept
#endif
    { return *this; }

private:
    proxies_type m_proxies;
};

} // namespace proxy

} // namespace v1

} // namespace otn
