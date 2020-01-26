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

#include <otn/v1/slim/spec.hpp>
#include <otn/v1/base/detail/token.hpp>
#include <otn/v1/generic/bind.hpp>

namespace otn
{

inline namespace v1
{

namespace slim
{

// T - Type

template <class T,
          class Deleter = generic::bind::deleter_t<T, basis::slim, ownership::unique>>
class unique_optional : public base::token<T, spec::slim::unique_optional<Deleter>>
{
private:
    using token = base::token<T, spec::slim::unique_optional<Deleter>>;

public:
    using token::token;
    using token::operator=;

    ~unique_optional() = default;
    unique_optional(const unique_optional&) = default;
    unique_optional(unique_optional&&)      = default;
    unique_optional& operator=(const unique_optional&) = default;
    unique_optional& operator=(unique_optional&&)      = default;
};

template <class T,
          class Deleter = generic::bind::deleter_t<T, basis::slim, ownership::unique>>
class unique_single : public base::token<T, spec::slim::unique_single<Deleter>>
{
private:
    using token = base::token<T, spec::slim::unique_single<Deleter>>;

public:
    using token::token;
    using token::operator=;

    ~unique_single() = default;
    unique_single(const unique_single&) = default;
    unique_single(unique_single&&)      = default;
    unique_single& operator=(const unique_single&) = default;
    unique_single& operator=(unique_single&&)      = default;
};

} // namespace slim

} // namespace v1

} // namespace otn
