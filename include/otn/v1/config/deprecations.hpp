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

#if defined OTN_STRICT
#define OTN_DEPRECATE_DEREFERENCE_OPTIONAL
#define OTN_DEPRECATE_MEMBER_OF_POINTER
#define OTN_DEPRECATE_SINGLE_BOOL
#endif

#if defined OTN_DEPRECATE_DEREFERENCE_OPTIONAL
#define OTN_DEREFERENCE_OPTIONAL_DEPRECATION \
    [[deprecated("dereferencing an optional in unchecked scope is not safe," \
                 " use 'gain' or 'access'")]]
#else
#define OTN_DEREFERENCE_OPTIONAL_DEPRECATION
#endif

#if defined OTN_DEPRECATE_MEMBER_OF_POINTER
#define OTN_MEMBER_OF_POINTER_DEPRECATION \
    [[deprecated("an object token is not a pointer")]]
#else
#define OTN_MEMBER_OF_POINTER_DEPRECATION
#endif

#if defined OTN_DEPRECATE_SINGLE_BOOL
#define OTN_SINGLE_BOOL_DEPRECATION \
    [[deprecated("a bool(single) is always true")]]
#else
#define OTN_SINGLE_BOOL_DEPRECATION
#endif

#ifdef _MSC_VER
#define OTN_SUPPRESS_DEPRECATIONS_BEGIN \
    __pragma(warning( push )) \
    __pragma(warning( disable : 4996 ))

#define OTN_SUPPRESS_DEPRECATIONS_END \
    __pragma(warning( pop ))
#else // _MSC_VER
#define OTN_SUPPRESS_DEPRECATIONS_BEGIN \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")

#define OTN_SUPPRESS_DEPRECATIONS_END \
    _Pragma("GCC diagnostic pop")
#endif // _MSC_VER
