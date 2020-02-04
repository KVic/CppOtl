# C++ OTL: Object Token Library

*Expressive, Safe, Consistent.*

The C++ Object Token Library (CppOtl) provides a set of tokens that are designed to manage an object's lifetime, similar to smart pointers from the C++ standard library. CppOtl contains tokens for unique and shared ownership of objects, weak observers for them, adds a unified type of ownership. Also, it introduces tokens with single (not_null) multiplicity, which can mitigate the "null references: billion-dollar mistake".

Tokens from CppOtl are integrated with smart pointers from the C++ standard library and can be consistently converted from one to another. CppOtl is intended for cases when there is not enough functionality of smart pointers from the C++ standard library and additional capabilities are required.

# Features

1. A set of consistent [tokens](#Tokens) that can express associative links, function parameters and variables [according to a UML model](doc/en/UML_Relations.md).
1. [`single`](doc/en/Characteristics.md#Single) tokens that always have a linked object and can not be empty.
1. [*trackable*](doc/en/Characteristics.md#Tracking) and *untrackable* tokens for appropriate use-case requirements.
1. The [`safe::weak`](doc/en/Characteristics.md#SafeWeak) can be created both from the `safe::unique` and the `safe::shared`. It will become *expired* (but not *dangling*) when an owner of a watched object is destroyed.
1. The [`safe::unified`](doc/en/Characteristics.md#SafeUnified) can temporarily prolong an object's lifetime in a given scope that allows finishing work with an object even other tokens is destroyed.
1. A constructor with the [`itself`](doc/en/Construction.md#itself_constructor) parameter allows a token itself to create an object with given attributes.
1. Algorithms for [unified access](doc/en/Access.md#One_Unified_if_else) to object tokens.
1. Tokens meet the requirements of `std::ranges::range`, that [allows to pass](doc/en/Characteristics.md#Range_access) them to functions that accept `range` argument.
1. [Traits](doc/en/Traits.md) allow recognizing characteristics of tokens in compile-time.
1. Focusing on maximum error detection in compile-time, several assertions in a debug build, minimum overhead in a release build, avoiding exceptions.
1. The ability to integrate CppOtl tokens with third-party pointers and tokens.

<a name="Tokens"></a>
# Tokens

All CppOtl entities are located in the `otn` namespace. **`otn`** is an abbreviation for **o**bject **t**oke**n**.

- [`safe`](doc/en/Characteristics.md#Safe) tokens provide an object's lifetime safety and can not be *dangling*.

   |Name|Description|
   |---|---|
   |`safe::unique[_single]<T>`|A unique single owner of an object.|
   |`safe::unique_optional<T>`|A unique optional owner of an object.|
   |`safe::shared[_single]<T>`|A shared single owner of an object.|
   |`safe::shared_optional<T>`|A shared optional owner of an object.|
   |`safe::weak_optional<T>`|An optional observer of an object owned by the `safe::unique` or `safe::shared`.|
   |`safe::unified[_single]<T>`|A unified single carrier and accessor of an object linked with `safe` tokens.|
   |`safe::unified_optional<T>`|A unified optional carrier and accessor of an object linked with `safe` tokens.|

- [`slim`](doc/en/Characteristics.md#Slim) tokens are lightweight with minimum runtime overhead.

   |Name|Description|
   |---|---|
   |`slim::unique[_single]<T, D>`|A unique single owner of an object.|
   |`slim::unique_optional<T, D>`|A unique optional owner of an object.|

- [`raw`](doc/en/Characteristics.md#Raw) tokens are close to raw C++ pointers.

   |Name|Description|
   |---|---|
   |`raw::weak[_single]<T>`|A single observer of an object.|
   |`raw::weak_optional<T>`|An optional observer of an object.|
   |`raw::unified[_single]<T>`|A unified single carrier and accessor of an object.|
   |`raw::unified_optional<T>`|A unified optional carrier and accessor of an object.|

Using `otn` tokens is similar to using smart pointers from the C++ standard library.

# Reference

- [Characteristics](doc/en/Characteristics.md)
- [Synopsis](doc/en/Synopsis.md)
- [Construction](doc/en/Construction.md)
- [Access](doc/en/Access.md)
- [Traits](doc/en/Traits.md)
- [UML relations](doc/en/UML_Relations.md)

# Requirements

C++17 compiler.

Tested with:

- GCC 9.2.1
- Clang 9.0.1

Note: It is a known issue that not all compilers can compile SFINAE "magic" from the [`otn/support/concept.hpp`](include/otn/v1/support/concept.hpp).

Note: Try the "feature/Cpp20Concepts" branch if a compiler supports C++20 Concepts.

# Usage

CppOtl is a header-only library.

Copy the `include/otn` directory to a compiler accessible place, add the path obtained to `include` to a compiler's *include paths*, and include the `otn/all.hpp` header file in a source code file.

# Examples

See the [Example](https://gitlab.com/CppObjectTokens/Complex/Example) complex.

# Tests

See the [Test/Token](https://gitlab.com/CppObjectTokens/Complex/Test/Token) complex.

# Current state

Beta version. Improving functionality, eliminating bugs, optimizing unoptimals.
