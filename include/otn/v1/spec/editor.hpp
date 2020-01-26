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

namespace otn
{

inline namespace v1
{

namespace spec
{

template <class Spec, class Type>
struct replace_type_t
{
    static_assert(sizeof(Spec) == -1,
                  "replace_type_t is defined for the Spec");
};

template <class Spec, class Basis>
struct replace_basis_t
{
    static_assert(sizeof(Spec) == -1,
                  "replace_basis_t is defined for the Spec");
};

template <class Spec, class Ownership>
struct replace_ownership_t
{
    static_assert(sizeof(Spec) == -1,
                  "replace_ownership_t is defined for the Spec");
};

template <class Spec, class Multiplicity>
struct replace_multiplicity_t
{
    static_assert(sizeof(Spec) == -1,
                  "replace_multiplicity_t is defined for the Spec");
};

template <class Spec, class Deleter>
struct replace_deleter_t
{
    static_assert(sizeof(Spec) == -1,
                  "replace_deleter_t is defined for the Spec");
};

template <class Spec, class Type>
using replace_type =
    typename replace_type_t<Spec, Type>::type;

template <class Spec, class Basis>
using replace_basis =
    typename replace_basis_t<Spec, Basis>::type;

template <class Spec, class Ownership>
using replace_ownership =
    typename replace_ownership_t<Spec, Ownership>::type;

template <class Spec, class Multiplicity>
using replace_multiplicity =
    typename replace_multiplicity_t<Spec, Multiplicity>::type;

template <class Spec, class Deleter>
using replace_deleter =
    typename replace_deleter_t<Spec, Deleter>::type;

} // namespace spec

} // namespace v1

} // namespace otn
