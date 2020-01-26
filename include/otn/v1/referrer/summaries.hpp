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

#include <otn/v1/referrer/rules.hpp>
#include <otn/v1/element/summaries.hpp>
#include <otn/v1/spec/traits.hpp>

namespace otn
{

inline namespace v1
{

namespace summaries
{

template <class T, class BriefSpec>
struct referrer
{
    static_assert(spec::is_brief_v<BriefSpec>,
                  "the BriefSpec must be the spec::brief");

    using brief_spec      = BriefSpec;
    using element_summary = summaries::element<T>;
    using element_type    = typename element_summary::type;

    static constexpr bool is_trackable =
        otn::referrer::enable_tracking<typename brief_spec::basis,
                                       typename brief_spec::ownership>;

    using type =
        otn::referrer::specify_t<element_type, brief_spec, is_trackable>;
};

} // namespace summaries

} // namespace v1

} // namespace otn
