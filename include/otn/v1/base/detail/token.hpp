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

#include <otn/v1/base/tags.hpp>
#include <otn/v1/base/configs.hpp>
#include <otn/v1/base/summaries.hpp>
#include <otn/v1/base/factory.hpp>
#include <otn/v1/base/detail/concepts.hpp>

#include <otn/v1/element/traits.hpp>

#include <otn/v1/referrer/summaries.hpp>
#include <otn/v1/referrer/adaptor.hpp>
#include <otn/v1/referrer/factory.hpp>
#include <otn/v1/referrer/tags.hpp>

#include <otn/v1/owner_base/rules.hpp>
#include <otn/v1/owner_base/traits.hpp>

#include <otn/v1/support/assert.hpp>
#include <otn/v1/support/noexcept.hpp>
#include <otn/v1/support/concept.hpp>
#include <otn/v1/support/pointer_traits.hpp>

namespace otn
{

inline namespace v1
{

namespace base
{

// T - Type

template <class T, class BriefSpec>
class token : private token_base
{
protected:
    using referrer_summary = summaries::referrer<T, BriefSpec>;
    using referrer_type    = typename referrer_summary::type;

public:
    using brief_spec   = typename referrer_summary::brief_spec;
    using element_type = typename referrer_summary::element_type;

protected:
    using element_summary = typename referrer_summary::element_summary;
    template <class Element>
    static constexpr bool is_convertible_from_element =
        element_summary::template is_convertible_from<Element>;
    template <class Element>
    static constexpr bool is_convertible_to_element =
        element_summary::template is_convertible_to<Element>;
    template <class Element>
    static constexpr bool is_incompatible_with_element =
        element_summary::template is_incompatible_with<Element>;
    template <class Element>
    static constexpr bool is_const_incorrect_with_element =
        element_summary::template is_const_incorrect_with<Element>;

    template <class Token>
    static constexpr bool is_convertible_from =
        is_convertible_from_element<otn::traits::element_t<Token>>;
    template <class Token>
    static constexpr bool is_convertible_to =
        is_convertible_to_element<otn::traits::element_t<Token>>;
    template <class Token>
    static constexpr bool is_incompatible_with =
        is_incompatible_with_element<otn::traits::element_t<Token>>;
    template <class Token>
    static constexpr bool is_const_incorrect_with =
        is_const_incorrect_with_element<otn::traits::element_t<Token>>;

    using kind = summaries::token_kind<brief_spec>;
    template <class Token>
    static constexpr bool copy_construction_enabled_from =
        kind::template operation_enabled_from<conversion::copy_construction, Token>;
    template <class Token>
    static constexpr bool copy_convertion_enabled_from =
        kind::template operation_enabled_to<conversion::copy_conversion, Token>;
    template <class Token>
    static constexpr bool copy_convertion_enabled_to =
        kind::template operation_enabled_from<conversion::copy_conversion, Token>;
    template <class Token>
    static constexpr bool move_construction_enabled_from =
        kind::template operation_enabled_from<conversion::move_construction, Token>;
    template <class Token>
    static constexpr bool move_construction_enabled_to =
        kind::template operation_enabled_to<conversion::move_construction, Token>;
    template <class Token>
    static constexpr bool move_convertion_enabled_from =
        kind::template operation_enabled_to<conversion::move_conversion, Token>;
    template <class Token>
    static constexpr bool move_convertion_enabled_to =
        kind::template operation_enabled_from<conversion::move_conversion, Token>;

    template <class Token>
    static constexpr bool copy_construction_explicit_from =
        kind::template operation_explicit_from<conversion::copy_construction, Token>;
    template <class Token>
    static constexpr bool copy_convertion_explicit_to =
        kind::template operation_explicit_from<conversion::copy_conversion, Token>;
    template <class Token>
    static constexpr bool move_construction_explicit_from =
        kind::template operation_explicit_from<conversion::move_construction, Token>;
    template <class Token>
    static constexpr bool move_convertion_explicit_to =
        kind::template operation_explicit_from<conversion::move_conversion, Token>;

    template <class Token>
    static constexpr bool construction_implicit_enabled_from()
    {
        if constexpr (std::is_lvalue_reference_v<Token>)
            return copy_construction_enabled_from<otn::remove_cvref_t<Token>>
                   && !copy_construction_explicit_from<otn::remove_cvref_t<Token>>;
        else
            return move_construction_enabled_from<otn::remove_cvref_t<Token>>
                   && !move_construction_explicit_from<otn::remove_cvref_t<Token>>;
    }

    template <class Token>
    static constexpr bool construction_explicit_enabled_from()
    {
        if constexpr (std::is_lvalue_reference_v<Token>)
            return copy_construction_enabled_from<otn::remove_cvref_t<Token>>
                   && copy_construction_explicit_from<otn::remove_cvref_t<Token>>;
        else
            return move_construction_enabled_from<otn::remove_cvref_t<Token>>
                   && move_construction_explicit_from<otn::remove_cvref_t<Token>>;
    }

    template <class Token>
    static constexpr bool construction_not_enabled_from()
    {
        if constexpr (std::is_lvalue_reference_v<Token>)
            return !(  copy_construction_enabled_from<otn::remove_cvref_t<Token>>
                    || copy_convertion_enabled_from<otn::remove_cvref_t<Token>>);
        else
            return !(  move_construction_enabled_from<otn::remove_cvref_t<Token>>
                    || move_convertion_enabled_from<otn::remove_cvref_t<Token>>);
    }

    template <class With>
    static constexpr bool has_same_owner_base =
        owner_base::has_same_v<
            owner_base::specify_t<otn::traits::basis_t<referrer_type>,
                                  otn::traits::ownership_t<referrer_type>>,
            owner_base::specify_t<otn::traits::basis_t<With>,
                                  otn::traits::ownership_t<With>>>;

    template <class Token>
    static constexpr bool is_token_construction_noexcept()
    {
        return noexcept(referrer_type{
                        referrer::adapt<referrer_type>(
                            std::declval<Token>())});
    }

    static constexpr bool is_copy_noexcept()
    {
        if constexpr (copy_construction_enabled_from<referrer_type>)
            return is_token_construction_noexcept<const referrer_type&>();
        else
            return true;
    }

    static constexpr bool is_move_noexcept()
    {
        if constexpr (move_construction_enabled_from<referrer_type>)
            return is_token_construction_noexcept < referrer_type && > ();
        else
            return true;
    }

public:
    // Destructor
    ~token() = default;

    // Default constructors
    OTN_CONCEPT_REQUIRES_(kind::is_optional)
    constexpr token() noexcept {}

    OTN_CONCEPT_REQUIRES_(kind::is_single)
    token() = delete;

    // Nullptr constructors
    OTN_CONCEPT_REQUIRES_(kind::is_optional && copy_construction_enabled_from<T*>)
    constexpr token(std::nullptr_t) noexcept
        : token{} {}

    OTN_CONCEPT_REQUIRES_(kind::is_optional && !copy_construction_enabled_from<T*>)
    token(std::nullptr_t) = delete;

    OTN_CONCEPT_REQUIRES_(kind::is_single)
    token(std::nullptr_t) = delete;

    // Itself constructors
    template <class ... Args,
              OTN_CONCEPT_REQUIRES(kind::itself_construction_enabled
                                   // NOTE: Doesn't work with incomplete type.
                                   /*&& !std::is_abstract_v<T>*/)>
    explicit token(itself_t, Args&& ... args)
        : token{referrer::pure, referrer::make<element_type, brief_spec>(
                    std::forward<Args>(args) ...)}
    {
        static_assert(!std::is_abstract_v<element_type>,
                      "the element_type is not abstract");
    }

    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(  kind::itself_construction_enabled
                                  && is_convertible_from_element<Y>
                                  && !std::is_abstract_v<Y>)>
    explicit token(itself_type_t<Y>, Args&& ... args)
        : token{referrer::pure, referrer::make<Y, brief_spec>(
                    std::forward<Args>(args) ...)} {}

    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(  kind::itself_construction_enabled
                                  && is_incompatible_with_element<Y>)>
    token(itself_type_t<Y>, Args&& ... args) = delete;

    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(  kind::itself_construction_enabled
                                  && is_const_incorrect_with_element<Y>)>
    token(itself_type_t<Y>, Args&& ... args) = delete;

    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(  kind::itself_construction_enabled
                                  && std::is_abstract_v<Y>)>
    token(itself_type_t<Y>, Args&& ... args) = delete;

    template <class ... Args,
              OTN_CONCEPT_REQUIRES(!kind::itself_construction_enabled)>
    token(itself_t, Args&& ... args) = delete;

    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(!kind::itself_construction_enabled)>
    token(itself_type_t<Y>, Args&& ... args) = delete;

    // Copy constructors
    // TODO: Add concept constraint 'copy_construction_enabled_from<token>'
    // and '= delete'.
    token(const token& other) OTN_NOEXCEPT(is_copy_noexcept())
        : token{referrer::pure, other.referrer()}
    {
        static_assert(copy_construction_enabled_from<token>,
                      "token is copyable from token");
    }

    // Move constructors
    // TODO: Add concept constraint 'move_construction_enabled_from<token>'
    // and '= delete'.
    token(token&& other) OTN_NOEXCEPT(is_move_noexcept())
        : token{referrer::pure, std::move(other.referrer())}
    {
        static_assert(move_construction_enabled_from<token>,
                      "token is movable from token");
    }

    // Forwarding constructors
    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_from<Token>
                                  && construction_implicit_enabled_from<Token>())>
    token(Token&& other) OTN_NOEXCEPT(
        is_token_construction_noexcept<Token>())
        : token{referrer::gate, std::forward<Token>(other)} {}

    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_from<Token>
                                  && construction_explicit_enabled_from<Token>())>
    explicit token(Token&& other) OTN_NOEXCEPT(
        is_token_construction_noexcept<Token>())
        : token{referrer::gate, std::forward<Token>(other)} {}

    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_from<Token>
                                  && construction_not_enabled_from<Token>())>
    token(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(is_incompatible_with<Token>)>
    token(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(is_const_incorrect_with<Token>)>
    token(Token&& other) = delete;

    // Copy nullptr assignment operators
    OTN_CONCEPT_REQUIRES_(kind::is_optional && copy_construction_enabled_from<T*>)
    token& operator=(std::nullptr_t) noexcept
    {
        token{nullptr}.swap_unrestricted(*this);
        return *this;
    }

    OTN_CONCEPT_REQUIRES_(kind::is_optional && !copy_construction_enabled_from<T*>)
    token& operator=(std::nullptr_t) = delete;

    OTN_CONCEPT_REQUIRES_(kind::is_single)
    token& operator=(std::nullptr_t) = delete;

    // Copy assignment operators
    // TODO: Add concept constraint 'copy_construction_enabled_from<token>'
    // and '= delete'.
    token& operator=(const token& other) OTN_NOEXCEPT(
        noexcept(token { other }))
    {
        token{other}.swap_unrestricted(*this);
        return *this;
    }

    // Move assignment operators
    // TODO: Add concept constraint 'move_construction_enabled_from<token>'
    // and '= delete'.
    token& operator=(token&& other) OTN_NOEXCEPT(
        noexcept(token { std::move(other) }))
    {
        token{std::move(other)}.swap_unrestricted(*this);
        return *this;
    }

    // Forwarding assignment operators
    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_from<Token>
                                  && construction_implicit_enabled_from<Token>())>
    token& operator=(Token&& other) OTN_NOEXCEPT(
        noexcept(token { std::forward<Token>(other) }))
    {
        token{std::forward<Token>(other)}.swap_unrestricted(*this);
        return *this;
    }

    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_from<Token>
                                  && construction_not_enabled_from<Token>())>
    token& operator=(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(is_incompatible_with<Token>)>
    token& operator=(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(is_const_incorrect_with<Token>)>
    token& operator=(Token&& other) = delete;

    // Conversion functions
    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_to<Token>
                                  && copy_convertion_enabled_to<Token>
                                  && !copy_convertion_explicit_to<Token>)>
    operator Token() const & OTN_NOEXCEPT(
        noexcept(base::make<Token>((*this).referrer())))
    { return base::make<Token>((*this).referrer()); }

    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_to<Token>
                                  && copy_convertion_enabled_to<Token>
                                  && copy_convertion_explicit_to<Token>)>
    explicit operator Token() const & OTN_NOEXCEPT(
        noexcept(base::make<Token>((*this).referrer())))
    { return base::make<Token>((*this).referrer()); }

    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_to<Token>
                                  && move_convertion_enabled_to<Token>
                                  && !move_convertion_explicit_to<Token>)>
    operator Token() && OTN_NOEXCEPT(
        noexcept(base::make<Token>(std::move((*this).referrer()))))
    { return base::make<Token>(std::move((*this).referrer())); }

    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_to<Token>
                                  && move_convertion_enabled_to<Token>
                                  && move_convertion_explicit_to<Token>)>
    explicit operator Token() && OTN_NOEXCEPT(
        noexcept(base::make<Token>(std::move((*this).referrer()))))
    { return base::make<Token>(std::move((*this).referrer())); }

    template <class Token,
              OTN_CONCEPT_REQUIRES(  is_convertible_to<Token>
                                  && !move_convertion_enabled_to<Token>
                                  && copy_convertion_enabled_to<Token>)>
    operator Token() && = delete;

    // Modifiers
    // TODO: Is the 'release' the same as the 'operator='? Remove it?
    OTN_CONCEPT_REQUIRES_(kind::is_optional)
    void reset() noexcept
    { token{}.swap_unrestricted(*this); }

    OTN_CONCEPT_REQUIRES_(kind::is_single)
    void reset() = delete;

    void reset(std::nullptr_t) = delete;

    template <class Y, OTN_CONCEPT_REQUIRES(  is_convertible_from_element<Y>
                                           && copy_construction_enabled_from<Y*>)>
    void reset(Y* p) OTN_NOEXCEPT(is_token_construction_noexcept<Y*>())
    {
        if (!OTN_ASSERT_CHECK(non_self(p)))
            return;

        if constexpr (kind::is_single_owner)
            if (!OTN_ASSERT_CHECK(construct_from_valued_referrer(p)))
                return;

        token{p}.swap_unrestricted(*this);
    }

    template <class Y, OTN_CONCEPT_REQUIRES(  is_convertible_from_element<Y>
                                           && !copy_construction_enabled_from<Y*>)>
    void reset(Y* p) = delete;

    template <class Y, OTN_CONCEPT_REQUIRES(is_incompatible_with_element<Y>)>
    void reset(Y* p) = delete;

    template <class Y, OTN_CONCEPT_REQUIRES(is_const_incorrect_with_element<Y>)>
    void reset(Y* p) = delete;

    template <OTN_CONCEPT_REQUIRES(kind::is_owner)>
    void swap(token& other) noexcept
    {
        if constexpr (kind::is_single)
        {
            if (!OTN_ASSERT_CHECK(swap_with_valued(other)))
                return;

            const token& other = *this;
            if (!OTN_ASSERT_CHECK(swap_with_valued(other)))
                return;
        }

        (*this).swap_unrestricted(other);
    }

    template <OTN_CONCEPT_REQUIRES(kind::is_observer)>
    void swap(token& other) noexcept
    { (*this).swap_unrestricted(other); }

    // Observers
    OTN_CONCEPT_REQUIRES_(kind::is_optional && kind::dereferencing_enabled)
    OTN_DEREFERENCE_OPTIONAL_DEPRECATION
    element_type & operator*() const noexcept
    { return (*this).element(); }

    OTN_CONCEPT_REQUIRES_(kind::is_single && kind::dereferencing_enabled)
    element_type & operator*() const noexcept
    { return (*this).element(); }

    OTN_CONCEPT_REQUIRES_(kind::dereferencing_enabled)
    OTN_MEMBER_OF_POINTER_DEPRECATION
    element_type* operator->() const noexcept
    {
        OTN_ASSERT(access_to_valued_referrer());
        return otn::internal::to_address((*this).referrer());
    }

    OTN_CONCEPT_REQUIRES_(kind::is_optional && kind::direct_access_enabled)
    explicit operator bool() const noexcept
    { return static_cast<bool>((*this).referrer()); }

    OTN_CONCEPT_REQUIRES_(kind::is_single && kind::direct_access_enabled)
    OTN_SINGLE_BOOL_DEPRECATION
    explicit constexpr operator bool() const noexcept
    { return true; }

    OTN_CONCEPT_REQUIRES_(kind::is_observer && referrer_summary::is_trackable)
    bool expired() const noexcept
    { return m_referrer.expired(); }

    template <class Y, class SpecY,
              OTN_CONCEPT_REQUIRES(has_same_owner_base<
                                       typename summaries::referrer<Y, SpecY>::type>)>
    bool owner_before(const token<Y, SpecY>& other) const noexcept
    {
        struct comparer : public token<Y, SpecY>::accessor
        {
            bool operator()(const token::referrer_type& a,
                            const token<Y, SpecY>& b) const noexcept
            { return a.owner_before((*this).referrer(b)); }
        };

        return comparer{} ((*this).referrer(), other);
    }

    template <template <class ... Args> class Referrer, class ... Args,
              OTN_CONCEPT_REQUIRES(has_same_owner_base<Referrer<Args ...>>)>
    bool owner_before(const Referrer<Args ...>& other) const noexcept
    { return (*this).referrer().owner_before(other); }

    // Tools
    class accessor
    {
    protected:
        using referrer_type = token::referrer_type;
        using element_type  = token::element_type;

        referrer_type& referrer(token& source) noexcept
        { return source.referrer(); }

        const referrer_type& referrer(const token& source) const noexcept
        { return source.referrer(); }

        OTN_CONCEPT_REQUIRES_(kind::direct_access_enabled)
        element_type & element(const token& source) const noexcept
        { return source.element(); }
    };

protected:
    // Forwarding constructors
    template <class Referrer>
    token(referrer::pure_t, Referrer&& other) OTN_NOEXCEPT(
        is_token_construction_noexcept<Referrer>())
        : m_referrer{assert_construct_from_referrer(
                         std::forward<Referrer>(other))}
    {}

    template <class Referrer>
    token(referrer::gate_t, Referrer&& other) OTN_NOEXCEPT(
        is_token_construction_noexcept<Referrer>())
        : token{referrer::pure,
                referrer::adapt<referrer_type>(std::forward<Referrer>(other))}
    {}

    // Access
    referrer_type& referrer() noexcept
    {
        if constexpr (kind::is_single_owner)
            OTN_ASSERT(access_to_valued_single());

        return m_referrer;
    }

    const referrer_type& referrer() const noexcept
    {
        if constexpr (kind::is_single_owner)
            OTN_ASSERT(access_to_valued_single());

        return m_referrer;
    }

    OTN_CONCEPT_REQUIRES_(kind::direct_access_enabled)
    element_type & element() const noexcept
    {
        OTN_ASSERT(access_to_valued_referrer());
        return *(*this).referrer();
    }

    // Support
    void swap_unrestricted(token& other) noexcept
    {
        using std::swap;
        swap(m_referrer, other.m_referrer);
    }

    // Contract conditions
    OTN_CONCEPT_REQUIRES_(kind::is_single_owner)
    bool access_to_valued_single() const noexcept
    { return static_cast<bool>(m_referrer); }

    OTN_CONCEPT_REQUIRES_(kind::dereferencing_enabled)
    bool access_to_valued_referrer() const noexcept
    { return static_cast<bool>(m_referrer); }

    template <class Referrer>
    Referrer && assert_construct_from_referrer(Referrer && other) const noexcept
    {
        if constexpr (kind::is_single_owner)
            OTN_ASSERT(construct_from_valued_referrer(other));

        return std::forward<Referrer>(other);
    }

    template <class Referrer>
    bool construct_from_valued_referrer(Referrer&& referrer) const noexcept
    { return static_cast<bool>(referrer); }

    template <class Y>
    bool non_self(Y* p) const noexcept
    {
        // TODO: Use C++20 std::to_address().
        auto referrer_address = otn::internal::to_address(m_referrer);
        return referrer_address == nullptr || referrer_address != p;
    }

    template <OTN_CONCEPT_REQUIRES(kind::is_single_owner)>
    bool swap_with_valued(const token& other) const noexcept
    { return static_cast<bool>(other.m_referrer); }

private:
    referrer_type m_referrer{};
};

} // namespace base

} // namespace v1

} // namespace otn
