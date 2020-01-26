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

#include <otn/v1/safe/spec.hpp>
#include <otn/v1/base/detail/token.hpp>

namespace otn
{

inline namespace v1
{

namespace safe
{

// T - Type

template <class T>
class unified_optional : public base::token<T, spec::safe::unified_optional>
{
private:
    using token = base::token<T, spec::safe::unified_optional>;

public:
    using token::token;
    using token::operator=;

    ~unified_optional() = default;
    unified_optional(const unified_optional&) = default;
    unified_optional(unified_optional&&)      = default;
    unified_optional& operator=(const unified_optional&) = default;
    unified_optional& operator=(unified_optional&&)      = default;
};

template <class T>
class unified_single : public base::token<T, spec::safe::unified_single>
{
private:
    using token = base::token<T, spec::safe::unified_single>;

public:
    using token::token;
    using token::operator=;

    ~unified_single() = default;
    unified_single(const unified_single&) = default;
    unified_single(unified_single&&)      = default;
    unified_single& operator=(const unified_single&) = default;
    unified_single& operator=(unified_single&&)      = default;
};

template <class T>
class unique_optional : public base::token<T, spec::safe::unique_optional>
{
private:
    using token = base::token<T, spec::safe::unique_optional>;

public:
    using token::token;
    using token::operator=;

    ~unique_optional() = default;
    unique_optional(const unique_optional&) = default;
    unique_optional(unique_optional&&)      = default;
    unique_optional& operator=(const unique_optional&) = default;
    unique_optional& operator=(unique_optional&&)      = default;
};

template <class T>
class unique_single : public base::token<T, spec::safe::unique_single>
{
private:
    using token = base::token<T, spec::safe::unique_single>;

public:
    using token::token;
    using token::operator=;

    ~unique_single() = default;
    unique_single(const unique_single&) = default;
    unique_single(unique_single&&)      = default;
    unique_single& operator=(const unique_single&) = default;
    unique_single& operator=(unique_single&&)      = default;
};

template <class T>
class shared_optional : public base::token<T, spec::safe::shared_optional>
{
private:
    using token = base::token<T, spec::safe::shared_optional>;

public:
    using token::token;
    using token::operator=;

    ~shared_optional() = default;
    shared_optional(const shared_optional&) = default;
    shared_optional(shared_optional&&)      = default;
    shared_optional& operator=(const shared_optional&) = default;
    shared_optional& operator=(shared_optional&&)      = default;
};

template <class T>
class shared_single : public base::token<T, spec::safe::shared_single>
{
private:
    using token = base::token<T, spec::safe::shared_single>;

public:
    using token::token;
    using token::operator=;

    ~shared_single() = default;
    shared_single(const shared_single&) = default;
    shared_single(shared_single&&)      = default;
    shared_single& operator=(const shared_single&) = default;
    shared_single& operator=(shared_single&&)      = default;
};

template <class T>
class weak_optional : public base::token<T, spec::safe::weak_optional>
{
private:
    using token = base::token<T, spec::safe::weak_optional>;

public:
    using token::token;
    using token::operator=;

    ~weak_optional() = default;
    weak_optional(const weak_optional&) = default;
    weak_optional(weak_optional&&)      = default;
    weak_optional& operator=(const weak_optional&) = default;
    weak_optional& operator=(weak_optional&&)      = default;
};

} // namespace safe

} // namespace v1

} // namespace otn
