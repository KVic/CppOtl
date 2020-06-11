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

#include <otn/v1/cpp_lang/origin.hpp>

#include <memory>

namespace std
{

// T - Type

template <class T>
struct pointer_traits<otn::cpp_lang::unified_optional<T>>
    : pointer_traits<T*>
{
    using element_type = typename pointer_traits<T*>::element_type;
    using pointer      = otn::cpp_lang::unified_optional<T>;

    static element_type* to_address(const pointer& p) noexcept
    { return p; }
};

template <class T>
struct pointer_traits<otn::cpp_lang::thin_optional<T>>
{
    using element_type    = typename otn::cpp_lang::thin_optional<T>::element_type;
    using difference_type = std::ptrdiff_t;
    using pointer         = otn::cpp_lang::thin_optional<T>;

    template <class U>
    using rebind = otn::cpp_lang::thin_optional<U>;

    static element_type* to_address(const pointer& p) noexcept
    { return static_cast<element_type*>(p); }
};

template <class T>
struct pointer_traits<otn::cpp_lang::thin_single<T>>
{
    using element_type    = typename otn::cpp_lang::thin_single<T>::element_type;
    using difference_type = std::ptrdiff_t;
    using pointer         = otn::cpp_lang::thin_single<T>;

    template <class U>
    using rebind = otn::cpp_lang::thin_single<U>;

    static element_type* to_address(const pointer& p) noexcept
    { return static_cast<element_type*>(p); }
};

} // namespace std
