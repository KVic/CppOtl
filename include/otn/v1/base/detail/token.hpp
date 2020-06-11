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

#include <otn/v1/config/deprecations.hpp>

#include <otn/v1/base/detail/concepts.hpp>
#include <otn/v1/base/summaries.hpp>
#include <otn/v1/base/traits.hpp>

#include <otn/v1/element/traits.hpp>

#include <otn/v1/referrer/summaries.hpp>
#include <otn/v1/referrer/adaptor.hpp>
#include <otn/v1/referrer/factory.hpp>

#include <otn/v1/owner_base/rules.hpp>
#include <otn/v1/owner_base/traits.hpp>

#include <otn/v1/tag/itself.hpp>

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
    // Element traits.
    // NOTE: Disabling element traits can speed up the debug build (~5%).
    template <class Element>
    static constexpr bool is_convertible_from_element =
        is_elements_convertible<Element, element_type>;
    template <class Element>
    static constexpr bool is_incompatible_with_element =
        is_elements_incompatible<element_type, Element>;
    template <class Element>
    static constexpr bool is_const_incorrect_with_element =
        is_elements_const_incorrect<element_type, Element>;

    template <class Token>
    static constexpr bool is_element_convertible_from =
        is_convertible_from_element<otn::traits::element_t<Token>>;
    template <class Token>
    static constexpr bool is_element_convertible_to =
        is_elements_convertible<element_type, otn::traits::element_t<Token>>;
    template <class Token>
    static constexpr bool is_element_incompatible_with =
        is_incompatible_with_element<otn::traits::element_t<Token>>;
    template <class Token>
    static constexpr bool is_element_const_incorrect_with =
        is_const_incorrect_with_element<otn::traits::element_t<Token>>;

    // Referrer traits.
    // NOTE: Disabling referrer traits can speed up the debug build (~5%).
    template <class Element, class ... Args>
    static constexpr bool is_itself_constructible =
        referrer::factory<referrer_type>::template
        is_constructible<Element, Args...>;
    template <class Element, class ... Args>
    static constexpr bool is_itself_nothrow_constructible =
        referrer::factory<referrer_type>::template
        is_nothrow_constructible<Element, Args...>;

    static constexpr bool is_referrer_copy_constructible =
        referrer::adaptor<referrer_type, referrer_type>::is_copy_constructible;

    static constexpr bool is_referrer_move_constructible =
        referrer::adaptor<referrer_type, referrer_type>::is_move_constructible;

    static constexpr bool is_referrer_copy_assignable =
        referrer::adaptor<referrer_type, referrer_type>::is_copy_assignable;

    static constexpr bool is_referrer_move_assignable =
        referrer::adaptor<referrer_type, referrer_type>::is_move_assignable;

    template <class Token>
    static constexpr bool is_referrer_constructible_from =
        std::is_lvalue_reference_v<Token>
        ? referrer::adaptor<referrer_type,
                            otn::remove_cvref_t<Token>>::is_copy_constructible
        : referrer::adaptor<referrer_type,
                            otn::remove_cvref_t<Token>>::is_move_constructible;

    template <class Token>
    static constexpr bool is_referrer_assignable_from =
        std::is_lvalue_reference_v<Token>
        ? referrer::adaptor<referrer_type,
                            otn::remove_cvref_t<Token>>::is_copy_assignable
        : referrer::adaptor<referrer_type,
                            otn::remove_cvref_t<Token>>::is_move_assignable;

    template <class Token>
    static constexpr bool is_referrer_copy_convertible_to =
        referrer::adaptor<otn::remove_cvref_t<Token>,
                          referrer_type>::is_copy_constructible;

    template <class Token>
    static constexpr bool is_referrer_move_convertible_to =
        referrer::adaptor<otn::remove_cvref_t<Token>,
                          referrer_type>::is_move_constructible;

    // Conversion traits.
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
    static constexpr bool construction_implicit_enabled_from =
        std::is_lvalue_reference_v<Token>
        ? (  copy_construction_enabled_from<otn::remove_cvref_t<Token>>
          && !copy_construction_explicit_from<otn::remove_cvref_t<Token>>)
        : (  move_construction_enabled_from<otn::remove_cvref_t<Token>>
          && !move_construction_explicit_from<otn::remove_cvref_t<Token>>);

    template <class Token>
    static constexpr bool construction_explicit_enabled_from =
        std::is_lvalue_reference_v<Token>
        ? (  copy_construction_enabled_from<otn::remove_cvref_t<Token>>
          && copy_construction_explicit_from<otn::remove_cvref_t<Token>>)
        : (  move_construction_enabled_from<otn::remove_cvref_t<Token>>
          && move_construction_explicit_from<otn::remove_cvref_t<Token>>);

    template <class Token>
    static constexpr bool construction_not_enabled_from =
        std::is_lvalue_reference_v<Token>
        ? !(  copy_construction_enabled_from<otn::remove_cvref_t<Token>>
           || copy_convertion_enabled_from<otn::remove_cvref_t<Token>>)
        : !(  move_construction_enabled_from<otn::remove_cvref_t<Token>>
           || move_convertion_enabled_from<otn::remove_cvref_t<Token>>);

    // Owner base traits.
    template <class With>
    static constexpr bool has_same_owner_base =
        owner_base::has_same_v<
            owner_base::specify_t<otn::traits::basis_t<referrer_type>,
                                  otn::traits::ownership_t<referrer_type>>,
            owner_base::specify_t<otn::traits::basis_t<With>,
                                  otn::traits::ownership_t<With>>>;

public:
    // Destructor
    ~token() = default;

    // Default constructors
#ifdef __cpp_concepts
    constexpr token() noexcept
    requires(kind::is_optional) {}

    token()
    requires(kind::is_single) = delete;
#else
    OTN_CONCEPT_REQUIRES_(kind::is_optional)
    constexpr token() noexcept {}

    OTN_CONCEPT_REQUIRES_(kind::is_single)
    token() = delete;
#endif

    // Nullptr constructors
#ifdef __cpp_concepts
    constexpr token(std::nullptr_t) noexcept
    requires(kind::is_optional && copy_construction_enabled_from<T*>)
        : token{} {}

    token(std::nullptr_t)
    requires(kind::is_optional && !copy_construction_enabled_from<T*>) = delete;

    token(std::nullptr_t)
    requires(kind::is_single) = delete;
#else
    OTN_CONCEPT_REQUIRES_(kind::is_optional && copy_construction_enabled_from<T*>)
    constexpr token(std::nullptr_t) noexcept : token{} {}

    OTN_CONCEPT_REQUIRES_(kind::is_optional && !copy_construction_enabled_from<T*>)
    token(std::nullptr_t) = delete;

    OTN_CONCEPT_REQUIRES_(kind::is_single)
    token(std::nullptr_t) = delete;
#endif

    // Itself constructors
#ifdef __cpp_concepts
    template <class ... Args>
    requires(kind::itself_construction_enabled
             // NOTE: Doesn't work with incomplete type.
             /*&& is_itself_constructible<element_type, Args...>*/)
#else
    template <class ... Args,
              OTN_CONCEPT_REQUIRES(kind::itself_construction_enabled
                                   // NOTE: Doesn't work with incomplete type.
                                   /*&& is_itself_constructible<element_type, Args...>*/)>
#endif
    explicit token(itself_t, Args&& ... args) OTN_NOEXCEPT(
        (is_itself_nothrow_constructible<element_type, Args...>))
        : m_referrer{referrer::make<referrer_type, element_type>(
                         std::forward<Args>(args) ...)}
    {
        static_assert(is_itself_constructible<element_type, Args...>,
                      "the element_type is constructible from Args");

        OTN_ASSERT(constructed_with_valued_referrer());
    }

#ifdef __cpp_concepts
    template <class Y, class ... Args>
    requires(  kind::itself_construction_enabled
            && is_convertible_from_element<Y>
            && is_itself_constructible<Y, Args...>)
#else
    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(  kind::itself_construction_enabled
                                  && is_convertible_from_element<Y>
                                  && is_itself_constructible<Y, Args...>)>
#endif
    explicit token(itself_type_t<Y>, Args&& ... args) OTN_NOEXCEPT(
        (is_itself_nothrow_constructible<Y, Args...>))
        : m_referrer{referrer::make<referrer_type, Y>(
                         std::forward<Args>(args) ...)}
    {
        OTN_ASSERT(constructed_with_valued_referrer());
    }

#ifdef __cpp_concepts
    template <class Y, class ... Args>
    requires(  kind::itself_construction_enabled
            && is_convertible_from_element<Y>
            && !is_itself_constructible<Y, Args...>)
    token(itself_type_t<Y>, Args&& ... args) = delete;

    template <class Y, class ... Args>
    requires(  kind::itself_construction_enabled
            && is_incompatible_with_element<Y>)
    token(itself_type_t<Y>, Args&& ... args) = delete;

    template <class Y, class ... Args>
    requires(  kind::itself_construction_enabled
            && is_const_incorrect_with_element<Y>)
    token(itself_type_t<Y>, Args&& ... args) = delete;

    template <class ... Args>
    requires(!kind::itself_construction_enabled)
    token(itself_t, Args&& ... args) = delete;

    template <class Y, class ... Args>
    requires(!kind::itself_construction_enabled)
    token(itself_type_t<Y>, Args&& ... args) = delete;
#else
    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(  kind::itself_construction_enabled
                                  && is_convertible_from_element<Y>
                                  && !is_itself_constructible<Y, Args...>)>
    token(itself_type_t<Y>, Args&& ... args) = delete;

    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(  kind::itself_construction_enabled
                                  && is_incompatible_with_element<Y>)>
    token(itself_type_t<Y>, Args&& ... args) = delete;

    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(  kind::itself_construction_enabled
                                  && is_const_incorrect_with_element<Y>)>
    token(itself_type_t<Y>, Args&& ... args) = delete;

    template <class ... Args,
              OTN_CONCEPT_REQUIRES(!kind::itself_construction_enabled)>
    token(itself_t, Args&& ... args) = delete;

    template <class Y, class ... Args,
              OTN_CONCEPT_REQUIRES(!kind::itself_construction_enabled)>
    token(itself_type_t<Y>, Args&& ... args) = delete;
#endif

    // Copy constructors
#ifdef __cpp_concepts
    token(const token& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_copy_nothrow<referrer_type, referrer_type>))
    requires(  kind::copy_construction_enabled
            && is_referrer_copy_constructible)
        : m_referrer{other.referrer()}
    {
        if constexpr (kind::is_single)
            OTN_ASSERT(constructed_with_valued_referrer());
    }

    token(const token& other)
    requires(!kind::copy_construction_enabled) = delete;

    token(const token& other)
    requires(!is_referrer_copy_constructible) = delete;
#else
    token(const token& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_copy_nothrow<referrer_type, referrer_type>))
        : m_referrer{other.referrer()}
    {
        static_assert(kind::copy_construction_enabled,
                      "copy construction of the token is enabled");
        static_assert(is_referrer_copy_constructible,
                      "referrer of the token is copy constructible");

        if constexpr (kind::is_single)
            OTN_ASSERT(constructed_with_valued_referrer());
    }
#endif

    // Move constructors
#ifdef __cpp_concepts
    token(token&& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_move_nothrow<referrer_type, referrer_type>))
    requires(  kind::move_construction_enabled
            && is_referrer_move_constructible)
        : m_referrer{std::move(other.referrer())}
    {
        if constexpr (kind::is_single)
            OTN_ASSERT(constructed_with_valued_referrer());
    }

    token(token&& other)
    requires(!kind::move_construction_enabled) = delete;

    token(token&& other)
    requires(!is_referrer_move_constructible) = delete;
#else
    token(token&& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_move_nothrow<referrer_type, referrer_type>))
        : m_referrer{std::move(other.referrer())}
    {
        static_assert(kind::move_construction_enabled,
                      "move construction of the token is enabled");
        static_assert(is_referrer_move_constructible,
                      "referrer of the token is move constructible");

        if constexpr (kind::is_single)
            OTN_ASSERT(constructed_with_valued_referrer());
    }
#endif

    // Forwarding constructors
#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && construction_implicit_enabled_from<Token>
            && is_element_convertible_from<Token>
            && is_referrer_constructible_from<Token>)
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && construction_implicit_enabled_from<Token>
                                  && is_element_convertible_from<Token>
                                  && is_referrer_constructible_from<Token>)>
#endif
    token(Token&& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_nothrow<referrer_type, Token>))
        : m_referrer{referrer::adapt<referrer_type>(
                         assert_construct_from_referrer(std::forward<Token>(other)))}
    {
        if constexpr (kind::is_single)
            OTN_ASSERT(constructed_with_valued_referrer());
    }

#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && construction_explicit_enabled_from<Token>
            && is_element_convertible_from<Token>
            && is_referrer_constructible_from<Token>)
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && construction_explicit_enabled_from<Token>
                                  && is_element_convertible_from<Token>
                                  && is_referrer_constructible_from<Token>)>
#endif
    explicit token(Token&& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_nothrow<referrer_type, Token>))
        : m_referrer{referrer::adapt<referrer_type>(
                         assert_construct_from_referrer(std::forward<Token>(other)))}
    {
        if constexpr (kind::is_single)
            OTN_ASSERT(constructed_with_valued_referrer());
    }

#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && is_element_convertible_from<Token>
            && construction_not_enabled_from<Token>)
    token(Token&& other) = delete;

    template <class Token>
    requires(  otn::is_token_v<Token>
            && is_element_convertible_from<Token>
            && !is_referrer_constructible_from<Token>)
    token(Token&& other) = delete;

    template <class Token>
    requires(  otn::is_token_v<Token>
            && is_element_incompatible_with<Token>)
    token(Token&& other) = delete;

    template <class Token>
    requires(  otn::is_token_v<Token>
            && is_element_const_incorrect_with<Token>)
    token(Token&& other) = delete;
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && is_element_convertible_from<Token>
                                  && construction_not_enabled_from<Token>)>
    token(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && is_element_convertible_from<Token>
                                  && !is_referrer_constructible_from<Token>)>
    token(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && is_element_incompatible_with<Token>)>
    token(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && is_element_const_incorrect_with<Token>)>
    token(Token&& other) = delete;
#endif

    // Copy nullptr assignment operators
#ifdef __cpp_concepts
    token& operator=(std::nullptr_t) noexcept
    requires(kind::is_optional && copy_construction_enabled_from<T*>)
#else
    OTN_CONCEPT_REQUIRES_(kind::is_optional && copy_construction_enabled_from<T*>)
    token& operator=(std::nullptr_t) noexcept
#endif
    {
        token{nullptr}.swap_unrestricted(*this);
        return *this;
    }

#ifdef __cpp_concepts
    token& operator=(std::nullptr_t)
    requires(kind::is_optional && !copy_construction_enabled_from<T*>) = delete;

    token& operator=(std::nullptr_t)
    requires(kind::is_single) = delete;
#else
    OTN_CONCEPT_REQUIRES_(kind::is_optional && !copy_construction_enabled_from<T*>)
    token& operator=(std::nullptr_t) = delete;

    OTN_CONCEPT_REQUIRES_(kind::is_single)
    token& operator=(std::nullptr_t) = delete;
#endif

    // Copy assignment operators
#ifdef __cpp_concepts
    token& operator=(const token& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_copy_nothrow<referrer_type, referrer_type>))
    requires(  kind::copy_construction_enabled
            && is_referrer_copy_assignable)
    {
        token{other}.swap_unrestricted(*this);
        return *this;
    }

    token& operator=(const token& other)
    requires(!kind::copy_construction_enabled) = delete;

    token& operator=(const token& other)
    requires(!is_referrer_copy_assignable) = delete;
#else
    token& operator=(const token& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_copy_nothrow<referrer_type, referrer_type>))
    {
        token{other}.swap_unrestricted(*this);
        return *this;
    }
#endif

    // Move assignment operators
#ifdef __cpp_concepts
    token& operator=(token&& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_move_nothrow<referrer_type, referrer_type>))
    requires(  kind::move_construction_enabled
            && is_referrer_move_assignable)
    {
        token{std::move(other)}.swap_unrestricted(*this);
        return *this;
    }

    token& operator=(token&& other)
    requires(!kind::move_construction_enabled) = delete;

    token& operator=(token&& other)
    requires(!is_referrer_move_assignable) = delete;
#else
    token& operator=(token&& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_move_nothrow<referrer_type, referrer_type>))
    {
        token{std::move(other)}.swap_unrestricted(*this);
        return *this;
    }
#endif

    // Forwarding assignment operators
#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && construction_implicit_enabled_from<Token>
            && is_element_convertible_from<Token>
            && is_referrer_assignable_from<Token>)
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && construction_implicit_enabled_from<Token>
                                  && is_element_convertible_from<Token>
                                  && is_referrer_assignable_from<Token>)>
#endif
    token& operator=(Token&& other) OTN_NOEXCEPT(
        (referrer::is_adaptor_nothrow<referrer_type, Token>))
    {
        token{std::forward<Token>(other)}.swap_unrestricted(*this);
        return *this;
    }

#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && is_element_convertible_from<Token>
            && construction_not_enabled_from<Token>)
    token& operator=(Token && other) = delete;

    template <class Token>
    requires(  otn::is_token_v<Token>
            && is_element_convertible_from<Token>
            && !is_referrer_assignable_from<Token>)
    token& operator=(Token && other) = delete;

    template <class Token>
    requires(  otn::is_token_v<Token>
            && is_element_incompatible_with<Token>)
    token& operator=(Token && other) = delete;

    template <class Token>
    requires(  otn::is_token_v<Token>
            && is_element_const_incorrect_with<Token>)
    token& operator=(Token && other) = delete;
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && is_element_convertible_from<Token>
                                  && construction_not_enabled_from<Token>)>
    token& operator=(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && is_element_convertible_from<Token>
                                  && !is_referrer_assignable_from<Token>)>
    token& operator=(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && is_element_incompatible_with<Token>)>
    token& operator=(Token&& other) = delete;

    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && is_element_const_incorrect_with<Token>)>
    token& operator=(Token&& other) = delete;
#endif

    // Conversion functions
#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && copy_convertion_enabled_to<Token>
            && !copy_convertion_explicit_to<Token>
            && is_element_convertible_to<Token>
            && is_referrer_copy_convertible_to<Token>)
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && copy_convertion_enabled_to<Token>
                                  && !copy_convertion_explicit_to<Token>
                                  && is_element_convertible_to<Token>
                                  && is_referrer_copy_convertible_to<Token>)>
#endif
    operator Token() const & OTN_NOEXCEPT(
        (referrer::is_adaptor_copy_nothrow<Token, referrer_type>))
    { return referrer::adapt<Token>((*this).referrer()); }

#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && copy_convertion_enabled_to<Token>
            && copy_convertion_explicit_to<Token>
            && is_element_convertible_to<Token>
            && is_referrer_copy_convertible_to<Token>)
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && copy_convertion_enabled_to<Token>
                                  && copy_convertion_explicit_to<Token>
                                  && is_element_convertible_to<Token>
                                  && is_referrer_copy_convertible_to<Token>)>
#endif
    explicit operator Token() const & OTN_NOEXCEPT(
        (referrer::is_adaptor_copy_nothrow<Token, referrer_type>))
    { return referrer::adapt<Token>((*this).referrer()); }

#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && move_convertion_enabled_to<Token>
            && !move_convertion_explicit_to<Token>
            && is_element_convertible_to<Token>
            && is_referrer_move_convertible_to<Token>)
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && move_convertion_enabled_to<Token>
                                  && !move_convertion_explicit_to<Token>
                                  && is_element_convertible_to<Token>
                                  && is_referrer_move_convertible_to<Token>)>
#endif
    operator Token() && OTN_NOEXCEPT(
        (referrer::is_adaptor_move_nothrow<Token, referrer_type>))
    { return referrer::adapt<Token>(std::move((*this).referrer())); }

#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && move_convertion_enabled_to<Token>
            && move_convertion_explicit_to<Token>
            && is_element_convertible_to<Token>
            && is_referrer_move_convertible_to<Token>)
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && move_convertion_enabled_to<Token>
                                  && move_convertion_explicit_to<Token>
                                  && is_element_convertible_to<Token>
                                  && is_referrer_move_convertible_to<Token>)>
#endif
    explicit operator Token() && OTN_NOEXCEPT(
        (referrer::is_adaptor_move_nothrow<Token, referrer_type>))
    { return referrer::adapt<Token>(std::move((*this).referrer())); }

#ifdef __cpp_concepts
    template <class Token>
    requires(  otn::is_token_v<Token>
            && !move_convertion_enabled_to<Token>
            && copy_convertion_enabled_to<Token>
            && is_element_convertible_to<Token>)
#else
    template <class Token,
              OTN_CONCEPT_REQUIRES(  otn::is_token_v<Token>
                                  && !move_convertion_enabled_to<Token>
                                  && copy_convertion_enabled_to<Token>
                                  && is_element_convertible_to<Token>)>
#endif
    operator Token() && = delete;

    // ----- internal
    // Modifiers
    static constexpr bool is_swappable =
        kind::move_construction_enabled && std::is_swappable_v<referrer_type>;
    static constexpr bool is_nothrow_swappable =
        std::is_nothrow_swappable_v<referrer_type>;

#ifdef __cpp_concepts
    void swap(token& other) OTN_NOEXCEPT(is_nothrow_swappable)
    requires(is_swappable && kind::is_owner)
#else
    OTN_CONCEPT_REQUIRES_(is_swappable && kind::is_owner)
    void swap(token& other) OTN_NOEXCEPT(is_nothrow_swappable)
#endif
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

#ifdef __cpp_concepts
    void swap(token& other) OTN_NOEXCEPT(is_nothrow_swappable)
    requires(is_swappable && kind::is_observer)
#else
    OTN_CONCEPT_REQUIRES_(is_swappable && kind::is_observer)
    void swap(token& other) OTN_NOEXCEPT(is_nothrow_swappable)
#endif
    { (*this).swap_unrestricted(other); }
    // ----- internal

    // Observers
    // operator*
#ifdef __cpp_concepts
    OTN_DEREFERENCE_OPTIONAL_DEPRECATION
    [[nodiscard]] element_type& operator*() const noexcept
    requires(kind::dereferencing_enabled && kind::is_optional)
#else
    OTN_CONCEPT_REQUIRES_(kind::dereferencing_enabled && kind::is_optional)
    OTN_DEREFERENCE_OPTIONAL_DEPRECATION
    [[nodiscard]] element_type& operator*() const noexcept
#endif
    { return (*this).element(); }

#ifdef __cpp_concepts
    [[nodiscard]] element_type& operator*() const noexcept
    requires(kind::dereferencing_enabled && kind::is_single)
#else
    OTN_CONCEPT_REQUIRES_(kind::dereferencing_enabled && kind::is_single)
    [[nodiscard]] element_type& operator*() const noexcept
#endif
    { return (*this).element(); }

#ifdef __cpp_concepts
    element_type& operator*() const noexcept
    requires(!kind::dereferencing_enabled) = delete;
#else
    OTN_CONCEPT_REQUIRES_(!kind::dereferencing_enabled)
    element_type & operator*() const = delete;
#endif

    // operator->
#ifdef __cpp_concepts
    OTN_MEMBER_OF_POINTER_DEPRECATION
    [[nodiscard]] element_type* operator->() const noexcept
    requires(kind::dereferencing_enabled)
#else
    OTN_CONCEPT_REQUIRES_(kind::dereferencing_enabled)
    OTN_MEMBER_OF_POINTER_DEPRECATION
    [[nodiscard]] element_type* operator->() const noexcept
#endif
    {
        OTN_ASSERT(access_to_valued_referrer());
        return otn::internal::to_address((*this).referrer());
    }

#ifdef __cpp_concepts
    element_type* operator->() const noexcept
    requires(!kind::dereferencing_enabled) = delete;
#else
    OTN_CONCEPT_REQUIRES_(!kind::dereferencing_enabled)
    element_type* operator->() const = delete;
#endif

    // operator bool
#ifdef __cpp_concepts
    [[nodiscard]] explicit operator bool() const & noexcept
    requires(kind::direct_access_enabled && kind::is_optional)
#else
    OTN_CONCEPT_REQUIRES_(kind::direct_access_enabled && kind::is_optional)
    [[nodiscard]] explicit operator bool() const & noexcept
#endif
    { return static_cast<bool>((*this).referrer()); }

#ifdef __cpp_concepts
    OTN_SINGLE_BOOL_DEPRECATION
    [[nodiscard]] explicit constexpr operator bool() const & noexcept
    requires(kind::direct_access_enabled && kind::is_single)
#else
    OTN_CONCEPT_REQUIRES_(kind::direct_access_enabled && kind::is_single)
    OTN_SINGLE_BOOL_DEPRECATION
    [[nodiscard]] explicit constexpr operator bool() const & noexcept
#endif
    { return true; }

#ifdef __cpp_concepts
    operator bool() const & noexcept
    requires(!kind::direct_access_enabled) = delete;
#else
    OTN_CONCEPT_REQUIRES_(!kind::direct_access_enabled)
    operator bool() const& = delete;
#endif

    operator bool() && = delete;

    // expired
#ifdef __cpp_concepts
    [[nodiscard]] bool expired() const noexcept
    requires(kind::is_observer && referrer_summary::is_trackable)
#else
    OTN_CONCEPT_REQUIRES_(kind::is_observer && referrer_summary::is_trackable)
    [[nodiscard]] bool expired() const noexcept
#endif
    { return m_referrer.expired(); }

    // owner_before
#ifdef __cpp_concepts
    template <class Y, class SpecY>
    requires(has_same_owner_base<
                 typename summaries::referrer<Y, SpecY>::type>)
#else
    template <class Y, class SpecY,
              OTN_CONCEPT_REQUIRES(has_same_owner_base<
                                       typename summaries::referrer<Y, SpecY>::type>)>
#endif
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

#ifdef __cpp_concepts
    template <template <class ... Args> class Referrer, class ... Args>
    requires(has_same_owner_base<Referrer<Args ...>>)
#else
    template <template <class ... Args> class Referrer, class ... Args,
              OTN_CONCEPT_REQUIRES(has_same_owner_base<Referrer<Args ...>>)>
#endif
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

#ifdef __cpp_concepts
        element_type& element(const token& source) const noexcept
        requires(kind::direct_access_enabled)
#else
        OTN_CONCEPT_REQUIRES_(kind::direct_access_enabled)
        element_type & element(const token& source) const noexcept
#endif
        { return source.element(); }
    };

protected:
    // Access
    referrer_type& referrer() noexcept
    {
        if constexpr (kind::is_single)
            OTN_ASSERT(access_to_valued_single());

        return m_referrer;
    }

    const referrer_type& referrer() const noexcept
    {
        if constexpr (kind::is_single)
            OTN_ASSERT(access_to_valued_single());

        return m_referrer;
    }

#ifdef __cpp_concepts
    element_type& element() const noexcept
    requires(kind::direct_access_enabled)
#else
    OTN_CONCEPT_REQUIRES_(kind::direct_access_enabled)
    element_type & element() const noexcept
#endif
    {
        OTN_ASSERT(access_to_valued_referrer());
        return *(*this).referrer();
    }

    // Support
    void swap_unrestricted(token& other) OTN_NOEXCEPT(is_nothrow_swappable)
    {
        using std::swap;
        swap(m_referrer, other.m_referrer);
    }

    // Contract conditions
#ifdef __cpp_concepts
    constexpr bool access_to_valued_single() const noexcept
    requires(kind::is_single)
#else
    OTN_CONCEPT_REQUIRES_(kind::is_single)
    constexpr bool access_to_valued_single() const noexcept
#endif
    { return static_cast<bool>(m_referrer); }

#ifdef __cpp_concepts
    constexpr bool access_to_valued_referrer() const noexcept
    requires(kind::dereferencing_enabled)
#else
    OTN_CONCEPT_REQUIRES_(kind::dereferencing_enabled)
    constexpr bool access_to_valued_referrer() const noexcept
#endif
    { return static_cast<bool>(m_referrer); }

    constexpr bool constructed_with_valued_referrer() const noexcept
    { return static_cast<bool>(m_referrer); }

    template <class Referrer>
    Referrer && assert_construct_from_referrer(Referrer && source) const noexcept
    {
        if constexpr (kind::is_single)
            OTN_ASSERT(construct_from_valued_referrer(source));

        return std::forward<Referrer>(source);
    }

    template <class Referrer>
    constexpr bool construct_from_valued_referrer(Referrer&& referrer) const noexcept
    {
        if constexpr (otn::is_single_v<Referrer>)
            return true;
        else if constexpr (otn::is_direct_accessible_v<Referrer>)
            return static_cast<bool>(referrer);
        else
            return !referrer.expired();
    }

#ifdef __cpp_concepts
    constexpr bool swap_with_valued(const token& other) const noexcept
    requires(kind::is_single)
#else
    OTN_CONCEPT_REQUIRES_(kind::is_single)
    constexpr bool swap_with_valued(const token& other) const noexcept
#endif
    { return static_cast<bool>(other.m_referrer); }

private:
    referrer_type m_referrer{};
};

} // namespace base

} // namespace v1

} // namespace otn
