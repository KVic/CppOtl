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

#include <otn/v1/safe/detail/token.hpp>

namespace std
{

// T - Type

template <class T>
struct pointer_traits<otn::safe::unified_optional<T>>
    : pointer_traits<otn::base::token<T, otn::spec::safe::unified_optional>> {};

template <class T>
struct pointer_traits<otn::safe::unified_single<T>>
    : pointer_traits<otn::base::token<T, otn::spec::safe::unified_single>> {};

template <class T>
struct pointer_traits<otn::safe::unique_optional<T>>
    : pointer_traits<otn::base::token<T, otn::spec::safe::unique_optional>> {};

template <class T>
struct pointer_traits<otn::safe::unique_single<T>>
    : pointer_traits<otn::base::token<T, otn::spec::safe::unique_single>> {};

template <class T>
struct pointer_traits<otn::safe::shared_optional<T>>
    : pointer_traits<otn::base::token<T, otn::spec::safe::shared_optional>> {};

template <class T>
struct pointer_traits<otn::safe::shared_single<T>>
    : pointer_traits<otn::base::token<T, otn::spec::safe::shared_single>> {};

template <class T>
struct pointer_traits<otn::safe::weak_optional<T>>
    : pointer_traits<otn::base::token<T, otn::spec::safe::weak_optional>> {};

} // namespace std
