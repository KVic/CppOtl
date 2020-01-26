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

#include <type_traits>
#include <utility>

namespace otn
{

inline namespace v1
{

namespace cpp_lang
{

template <class T>
class unified_optional
{
protected:
    template <class Y>
    using is_compatible_t = std::enable_if_t<std::is_convertible_v<Y*, T*>>;

public:
    // Destructor
    ~unified_optional() = default;

    // Default constructor
    unified_optional() = default;

    // Value constructors
    constexpr unified_optional(std::nullptr_t) noexcept
        : unified_optional{} {}

    constexpr unified_optional(T* p) noexcept
        : m_referrer{p} {}

    // Copy constructors
    unified_optional(const unified_optional&) = default;

    template <class Y, class = is_compatible_t<Y>>
    constexpr unified_optional(const unified_optional<Y>& other) noexcept
        : m_referrer{other.operator->()} {}

    // Move constructors
    constexpr unified_optional(unified_optional&& other) noexcept
        : unified_optional{std::as_const(other)}
    { other = nullptr; }

    template <class Y, class = is_compatible_t<Y>>
    constexpr unified_optional(unified_optional<Y>&& other) noexcept
        : unified_optional{std::as_const(other)}
    { other = nullptr; }

    // Copy assignment operators
    constexpr unified_optional& operator=(std::nullptr_t) noexcept
    { m_referrer = nullptr; return *this; }

    unified_optional& operator=(const unified_optional&) = default;

    template <class Y, class = is_compatible_t<Y>>
    constexpr unified_optional& operator=(const unified_optional<Y>& other) noexcept
    { m_referrer = other.operator->(); return *this; }

    // Move assignment operators
    constexpr unified_optional& operator=(unified_optional&& other) noexcept
    { return (*this).template operator=<T>(std::move(other)); }

    template <class Y, class = is_compatible_t<Y>>
    constexpr unified_optional& operator=(unified_optional<Y>&& other) noexcept
    {
        m_referrer = other.operator->();
        other      = nullptr;
        return *this;
    }

    // Conversion operators
    constexpr operator T*() const & noexcept { return m_referrer; }
    constexpr operator T*() && noexcept
    {
        T* referrer = m_referrer;
        m_referrer = nullptr;
        return referrer;
    }

    // Observers
    constexpr T& operator*() const noexcept  { return *m_referrer; }
    constexpr T* operator->() const noexcept { return m_referrer; }

    // Modifiers
    void reset() noexcept { m_referrer = nullptr; }
    void reset(std::nullptr_t) noexcept { reset(); }

    template <class Y, class = is_compatible_t<Y>>
    void reset(Y* p) noexcept { m_referrer = p; }

    void swap(unified_optional& other) noexcept
    {
        using std::swap;
        swap(m_referrer, other.m_referrer);
    }

private:
    T* m_referrer{};
};

} // namespace cpp_lang

} // namespace v1

} // namespace otn
