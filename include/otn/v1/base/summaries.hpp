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

#include <otn/v1/base/rules.hpp>
#include <otn/v1/lifetime/rules.hpp>
#include <otn/v1/conversion/rules.hpp>

#include <otn/v1/basis/traits.hpp>
#include <otn/v1/ownership/traits.hpp>
#include <otn/v1/multiplicity/traits.hpp>
#include <otn/v1/lifetime/traits.hpp>

namespace otn
{

inline namespace v1
{

namespace summaries
{

template <class BriefSpec>
struct token_kind
{
    using basis        = typename BriefSpec::basis;
    using ownership    = typename BriefSpec::ownership;
    using multiplicity = typename BriefSpec::multiplicity;
    using deleter      = typename BriefSpec::deleter;

    static constexpr bool itself_construction_enabled =
        otn::base::enable_itself_construction<basis, ownership>;

    static constexpr bool dereferencing_enabled =
        otn::base::enable_dereferencing<basis, ownership>;

    static constexpr bool direct_access_enabled =
        otn::base::enable_direct_access<basis, ownership>;

    static constexpr otn::lifetime::role lifetime_role =
        otn::lifetime::specify_role<basis, ownership, deleter>;

    static constexpr bool is_owner =
        otn::lifetime::is_owner_v<lifetime_role>;
    static constexpr bool is_observer =
        otn::lifetime::is_observer_v<lifetime_role>;

    static constexpr bool is_optional =
        otn::multiplicity::is_optional_v<multiplicity>;
    static constexpr bool is_single =
        otn::multiplicity::is_single_v<multiplicity>;

    static constexpr bool is_single_owner = is_single && is_owner;

    static constexpr bool self_copy_construction_enabled =
        conversion::property<conversion::copy_construction,
                             basis, ownership, multiplicity,
                             basis, ownership, multiplicity>::is_enabled;

    static constexpr bool self_move_construction_enabled =
        conversion::property<conversion::move_construction,
                             basis, ownership, multiplicity,
                             basis, ownership, multiplicity>::is_enabled;

    template <class Operation, class Token>
    static constexpr bool operation_enabled_from =
        conversion::property<Operation,
                             basis, ownership, multiplicity,
                             otn::traits::basis_t<Token>,
                             otn::traits::ownership_t<Token>,
                             otn::traits::multiplicity_t<Token>>::is_enabled;

    template <class Operation, class Token>
    static constexpr bool operation_enabled_to =
        conversion::property<Operation,
                             otn::traits::basis_t<Token>,
                             otn::traits::ownership_t<Token>,
                             otn::traits::multiplicity_t<Token>,
                             basis, ownership, multiplicity>::is_enabled;

    template <class Operation, class Token>
    static constexpr bool operation_explicit_from =
        conversion::property<Operation,
                             basis, ownership, multiplicity,
                             otn::traits::basis_t<Token>,
                             otn::traits::ownership_t<Token>,
                             otn::traits::multiplicity_t<Token>>::is_explicit;

    template <class Operation, class Token>
    static constexpr bool operation_explicit_to =
        conversion::property<Operation,
                             otn::traits::basis_t<Token>,
                             otn::traits::ownership_t<Token>,
                             otn::traits::multiplicity_t<Token>,
                             basis, ownership, multiplicity>::is_explicit;
};

} // namespace summaries

} // namespace v1

} // namespace otn
