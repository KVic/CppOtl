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

#include <otn/v1/access/functions.hpp>

#include <otn/v1/config/deprecations.hpp>

#include <tuple>

namespace otn
{

inline namespace v1
{

namespace internal
{

OTN_SUPPRESS_DEPRECATIONS_BEGIN

template <class ... Args, std::size_t ... Indices>
inline
auto access_if(const std::tuple<Args ...>& args,
               std::index_sequence<Indices...>)
{
    // This function is the weird form of:
    // template <class ... Tokens, class TokenFunction>
    // inline
    // auto access_if(Tokens&& ... tokens, TokenFunction&& success_handler);

    using namespace std;
    using args_t = tuple<Args && ...>;
    constexpr size_t last_index = sizeof... (Args) - 1;

    // The first arguments is a tokens.
    auto locs = gain(forward<tuple_element_t<Indices, args_t>>
                         (get<Indices>(args))...);

    if (locs)
        // The last argument is a success_handler function.
        // Call: success_handler(*tokens...);
        return get<last_index>(args)(*locs.template get<Indices>()...);
}

template <class ... Args, std::size_t ... Indices>
inline
auto access_if_else(const std::tuple<Args ...>& args,
                    std::index_sequence<Indices...>)
{
    // This function is the weird form of:
    // template <class ... Tokens, class TokenFunction, class EmptyFunction>
    // inline
    //    auto access_if_else(Tokens&& ...    tokens,
    //                        TokenFunction&& success_handler,
    //                        EmptyFunction&& failure_handler)

    using namespace std;
    using args_t = tuple<Args && ...>;
    constexpr size_t last_index = sizeof... (Args) - 1;

    // The first arguments is a tokens.
    auto locs = gain(forward<tuple_element_t<Indices, args_t>>
                         (get<Indices>(args))...);

    if (locs)
        // The penultimate argument is a success_handler function.
        // Call: success_handler(*tokens...);
        return get<last_index - 1>(args)(*locs.template get<Indices>()...);
    else
        // The last argument is a failure_handler function.
        // Call: failure_handler();
        return get<last_index>(args)();
}

OTN_SUPPRESS_DEPRECATIONS_END

} // namespace internal

template <class ... Args>
inline
auto access(Args&& ... args)
{
    using namespace std;
    using namespace internal;

    constexpr size_t args_count = sizeof... (Args);

    using args_t = tuple<Args && ...>;
    if constexpr (std::is_invocable_v<tuple_element_t<args_count - 1, args_t>>)
        return access_if_else(forward_as_tuple(forward<Args>(args) ...),
                              make_index_sequence<args_count - 2>{});
    else
        return access_if(forward_as_tuple(forward<Args>(args) ...),
                         make_index_sequence<args_count - 1>{});
}

} // namespace v1

} // namespace otn
