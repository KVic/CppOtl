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

template <class Proxies>
class iterator
{
public:
    using difference_type   = std::ptrdiff_t;
    using value_type        = const Proxies;
    using pointer           = value_type *;
    using reference         = value_type&;
    using iterator_category = std::forward_iterator_tag;

    iterator() = default;

    explicit iterator(const Proxies& proxies) noexcept
        : m_proxies{proxies ? std::addressof(proxies) : nullptr}
    {}

    constexpr explicit operator bool() const noexcept
    { return static_cast<bool>(m_proxies); }

    reference operator*() const noexcept
    { return *m_proxies; }
    iterator& operator++() noexcept
    { m_proxies = nullptr; return *this; }
    constexpr iterator operator++(int) const noexcept
    { return iterator{}; }

    bool operator==(const iterator& other) const noexcept
    { return other.m_proxies == m_proxies; }
    bool operator!=(const iterator& other) const noexcept
    { return !operator==(other); }

private:
    pointer m_proxies{};
};

} // namespace proxy

} // namespace v1

} // namespace otn
