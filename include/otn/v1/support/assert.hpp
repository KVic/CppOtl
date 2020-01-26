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

#include <string_view>
#include <cassert>

// TODO: Use the Contracts.

#if defined TOKEN_TEST_ASSERT
namespace otn
{

inline namespace v1
{

namespace internal
{

inline bool assert_check(bool condition,
                         std::string_view expression,
                         std::string_view file_name,
                         unsigned int     line_number,
                         std::string_view function_name)
{
    return ::Test::Assert::instance().check(
        condition,
        ::Test::ContractViolation{line_number,
                                  file_name,
                                  function_name,
                                  expression,
                                  {}});
}

} // namespace internal

} // namespace v1

} // namespace otn

#ifndef __PRETTY_FUNCTION__
#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#endif

#define OTN_ASSERT_CHECK(expr) \
    otn::internal::assert_check(static_cast<bool>(expr), #expr, \
                                __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define OTN_ASSERT(expr) OTN_ASSERT_CHECK(expr)
#else
#define OTN_ASSERT_CHECK(expr) (assert(expr), true)
#define OTN_ASSERT(expr) assert(expr)
#endif
