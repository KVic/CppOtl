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

#include <otn/v1/referrer/traits.hpp>
#include <otn/v1/base/traits.hpp>
#include <otn/v1/traits/derivative.hpp>
#include <otn/v1/proxy/factory.hpp>
#include <otn/v1/support/utilize.hpp>
#include <otn/v1/support/concept.hpp>

#include <iterator>

namespace otn
{

inline namespace v1
{

namespace collection
{

template <class Token, class = void>
class iterator
{
    static_assert(sizeof(Token) == -1,
                  "iterator is defined for the Token");
};

template <class Token>
class iterator<Token,
               std::enable_if_t<is_direct_accessible_v<Token>>>
{
public:
    using difference_type   = std::ptrdiff_t;
    using value_type        = Token;
    using pointer           = const value_type *;
    using reference         = const value_type&;
    using iterator_category = std::forward_iterator_tag;

    iterator() = default;

    OTN_CONCEPT_REQUIRES_(is_optional_v<Token>)
    explicit iterator(Token& token) noexcept
        : m_token{token ? std::addressof(token) : nullptr}
    {}

    OTN_CONCEPT_REQUIRES_(is_single_v<Token>)
    explicit iterator(Token& token) noexcept
        : m_token{std::addressof(token)}
    {}

    constexpr explicit operator bool() const noexcept
    {
        if constexpr (is_not_empty_v<Token>)
            return true;
        else
            return static_cast<bool>(m_token);
    }

    reference operator*() const noexcept
    {
        if (!OTN_ASSERT_CHECK(access_to_valued_referrer()))
            return *pointer{}; // Are you scared? ;)

        return *m_token;
    }
    iterator& operator++() noexcept
    { m_token = nullptr; return *this; }
    constexpr iterator operator++(int) const noexcept
    { return iterator{}; }

    bool operator==(const iterator& other) const noexcept
    { return other.m_token == m_token; }
    bool operator!=(const iterator& other) const noexcept
    { return !operator==(other); }

protected:
    bool access_to_valued_referrer() const noexcept
    { return static_cast<bool>(m_token); }

private:
    Token* m_token{};
};

template <class Token>
class iterator<Token,
               std::enable_if_t<is_proxy_accessible_v<Token>>>
{
protected:
    using token_proxy = decltype(proxy::make(std::declval<Token>()));

public:
    using difference_type   = std::ptrdiff_t;
    using value_type        = token_proxy;
    using pointer           = const value_type *;
    using reference         = const value_type&;
    using iterator_category = std::forward_iterator_tag;

    iterator() = default;

    explicit iterator(const Token& token) noexcept
        : m_proxy{proxy::make(token)}
    {}

    explicit operator bool() const noexcept
    { return static_cast<bool>(m_proxy); }

    reference operator*() const noexcept
    { return m_proxy; }
    iterator& operator++() noexcept
    { utilize(std::move(m_proxy)); return *this; }
    constexpr iterator operator++(int) const noexcept
    { return iterator{}; }

    bool operator==(const iterator& other) const noexcept
    { return other.m_proxy == m_proxy; }
    bool operator!=(const iterator& other) const noexcept
    { return !operator==(other); }

private:
    token_proxy m_proxy{};
};

} // namespace collection

} // namespace v1

} // namespace otn
