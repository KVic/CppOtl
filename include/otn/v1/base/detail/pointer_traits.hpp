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

#include <otn/v1/base/detail/token.hpp>
#include <otn/v1/base/traits.hpp>

namespace std
{

// T - Type

template <class T, class Spec>
struct pointer_traits<otn::base::token<T, Spec>>
{
    using pointer      = otn::base::token<T, Spec>;
    using element_type = typename pointer::element_type;

protected:
    struct accessor : public pointer::accessor
    {
    protected:
        using typename pointer::accessor::referrer_type;
        using referrer_traits = pointer_traits<referrer_type>;

    public:
        using difference_type = typename referrer_traits::difference_type;

        element_type& to_value(const pointer& p) const noexcept
        { return (*this).element(p); }

        element_type* to_address(const pointer& p) const noexcept
        {
            return otn::internal::to_address((*this).referrer(p));
            // TODO: Use C++20 std::to_address().
            // return std::to_address((*this).referrer(p));
        }
    };

public:
    using difference_type = typename accessor::difference_type;

    template <class U>
    using rebind = otn::base::token<U, Spec>;

    static element_type& to_value(const pointer& p) noexcept
    requires otn::is_direct_accessible_v<pointer>
    { return accessor{}.to_value(p); }

    static element_type& to_value(const pointer& p)
    requires !otn::is_direct_accessible_v<pointer> = delete;

    static element_type* to_address(const pointer& p) noexcept
    requires otn::is_direct_accessible_v<pointer>
    { return accessor{}.to_address(p); }

    static element_type* to_address(const pointer& p)
    requires otn::is_proxy_accessible_v<pointer> = delete;
};

} // namespace std
