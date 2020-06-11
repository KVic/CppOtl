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

#include <otn/v1/raw/detail/token.hpp>

namespace std
{

// T - Type

template <class T>
struct hash<otn::raw::unified_optional<T>>
    : hash<otn::base::token<T, otn::spec::raw::unified_optional>> {};

template <class T>
struct hash<otn::raw::unified_single<T>>
    : hash<otn::base::token<T, otn::spec::raw::unified_single>> {};

template <class T>
struct hash<otn::raw::unique_optional<T>>
    : hash<otn::base::token<T, otn::spec::raw::unique_optional>> {};

template <class T>
struct hash<otn::raw::unique_single<T>>
    : hash<otn::base::token<T, otn::spec::raw::unique_single>> {};

template <class T>
struct hash<otn::raw::weak_optional<T>>
    : hash<otn::base::token<T, otn::spec::raw::weak_optional>> {};

template <class T>
struct hash<otn::raw::weak_single<T>>
    : hash<otn::base::token<T, otn::spec::raw::weak_single>> {};

} // namespace std
