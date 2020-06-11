# Characteristics

Characteristics are defined for CppOtl scope.

1. [Ownership](#Ownership)
   1. [Unique](#Unique)
   1. [Shared](#Shared)
   1. [Weak](#Weak)
   1. [Unified](#Unified)
1. [Multiplicity](#Multiplicity)
   1. [Optional](#Optional)
   1. [Single](#Single)
   1. [Any](#Any)
   1. [Range access](#Range_access)
   1. [Suffix](#Suffix)
1. [Tracking](#Tracking)
   1. [Trackable](#Trackable)
   1. [Untrackable](#Untrackable)
1. [Basis](#Basis)
   1. [Safe](#Safe)
   1. [Slim](#Slim)
   1. [Raw](#Raw)

<a name="Ownership"></a>
# Ownership

An `owner` is a token that may delete a linked object. An *owner* can not be *dangling*.

An `observer` is a token that can not delete a linked object. An *observer* may be *dangling*.

<a name="Unique"></a>
## Unique

`unique` ownership defines that only one `unique` token can be an *owner* of a linked object at a time.

`unique` ownership is designed to express **composite** AggregationKind of the memberEnd of Association (see *"9.5 Properties"* in [UML 2.5.1](https://www.omg.org/spec/UML/2.5.1/PDF)):
> Composite aggregation is a strong form of aggregation that requires a part object be included in at most one composite object at a time. If a composite object is deleted, all of its part instances that are objects are deleted with it.

The primary goal of `unique` ownership is to provide the integrity of **composite** aggregation in the associative link between objects.

From the C++ point of view, a token with `unique` ownership is not copyable (but movable). It is designed to be primarily used as a data member of a class. It is also may be used as a local variable to create an object under `unique` ownership or as a parameter of a function to transfer `unique` ownership of an object.

<a name="Shared"></a>
## Shared

`shared` ownership defines that one or more `shared` tokens can be an *owner* of a linked object at a time.

`shared` ownership is designed to express **shared** AggregationKind of the memberEnd of Association (see *"9.5 Properties"* in [UML 2.5.1](https://www.omg.org/spec/UML/2.5.1/PDF)). The primary goal of `shared` ownership is to provide the integrity of **shared** aggregation in the associative link between objects.

From the C++ point of view, a token with `shared` ownership is copyable and movable. It is designed to be primarily used as a data member of a class. It is also may be used as a local variable to create an object under `shared` ownership or as a parameter of a function to transfer `shared` ownership of an object.

<a name="Weak"></a>
## Weak

`weak` ownership defines that a token is an *observer* of a linked object.

`weak` ownership is designed to express **none** AggregationKind of the memberEnd of Association (see *"9.5 Properties"* in [UML 2.5.1](https://www.omg.org/spec/UML/2.5.1/PDF)). The primary goal of `weak` ownership is to provide a memberEnd that opposite to **composite** or **shared** memberEnd of a binary association.

From the C++ point of view, a token with `weak` ownership is copyable and movable. It is designed to be primarily used as a data member of a class. It is also may be used as a local variable to create an *observer* of an object or as a parameter of a function to transfer `weak` ownership of an object.

<a name="Unified"></a>
## Unified

`unified` ownership is designed to express parameters (see *"9.4.3.4 Parameters"* in [UML 2.5.1](https://www.omg.org/spec/UML/2.5.1/PDF)) and variables (see *"15.2.3.5 Variables"*). The primary goal of `unified` ownership is transferring objects and accessing them.

From the C++ point of view, a token with `unified` ownership is copyable and movable. It is designed to be primarily used as a local variable to access an object linked to a token with other ownership or as a parameter of a function to transfer `unified` ownership of an object. 

**Warning: Do not use `unified` ownership as a data member of a class! Use `unified` ownership in the same use cases as a regular C++ reference `&`.**

<a name="Multiplicity"></a>
# Multiplicity

The multiplicity in CppOtl is inspired by the multiplicity from UML (see *"7.5 Types and Multiplicity"* in [UML 2.5.1](https://www.omg.org/spec/UML/2.5.1/PDF)). 

*7.5.3.2 Multiplicities*
> The cardinality of a collection is the number of values contained in that collection. The multiplicity of a MultiplicityElement specifies valid cardinalities of the collection it represents. The multiplicity is a constraint on the cardinality, which shall not be less than the lower bound and not greater than the upper bound specified for the multiplicity (unless the multiplicity is unlimited, in which case there is no constraint on the upper bound).

|`otn::multiplicity`|[lower..upper]|
|---|---|
|`unknown`|---|
|`optional`|[0..1]|
|`single`|[1..1]|
|`non_empty`|[1..*]|
|`any`|[0..*]|

<a name="Optional"></a>
## Optional

An `optional` token may have a linked object or may be empty. **It is important to check that a token has a linked object before accessing it**. A moved-from `optional` token is placed in a valid empty state. It is valid to use moved-from `optional` token.

<a name="Single"></a>
## Single

A `single` token always has a linked object and can not be empty. There is no need to check that token has a linked object, it can be accessed directly. A moved-from `single` token is placed in an invalid unspecified state. **It is invalid to access a moved-from `single` token, it only can be destroyed or assigned from another token.**

<a name="Any"></a>
## Any

CppOtl contains tokens only with `optional` and `single` multiplicity. To get a collection with a larger multiplicity prefer to use `single` tokens in some container (for example, `std::vector`).

<a name="Range_access"></a>
## Range access

`otn` tokens meet the requirements of `std::ranges::range`, they can be accessed by range-based for loop or passed to functions which accept `range` argument. There is no need to put a standalone `otn` token into an individual container.

<p>
<details>
<summary>Example</summary>

```c++
#include <otn/all.hpp>
#include <string>
#include <vector>
#include <iostream>

template <class Range>
void print(const std::string& caption, const Range& tokens)
{
    std::cout << caption << " [";
    for (auto& token : tokens)
        std::cout << " " << *token;
    std::cout << " ]" << std::endl;
}

int main()
{
    using namespace otn;

    unique<int>              a{itself, 7};
    weak_optional<int>       b = a;
    shared_optional<int>     c;
    std::vector<unique<int>> d;
    d.push_back(make_unique<int>(1));
    d.emplace_back(itself, 2);
    d.emplace_back(itself, 3);

    print("a:", a);
    print("b:", b);
    print("c:", c);
    print("d:", d);
}
```

Output:

```
a: [ 7 ]
b: [ 7 ]
c: [ ]
d: [ 1 2 3 ]
```

</details>
</p>

<a name="Suffix"></a>
## Suffix

`otn` tokens with a name that has no suffix are `single` by default (for example, `otn::unique`). However, they have aliases with explicit `_single` suffix (`otn::unique_single`). `optional` tokens have a name with `_optional` suffix (`otn::unique_optional`).

<a name="Tracking"></a>
# Tracking

***Tracking*** is the ability of an *observer* to detect that a linked object was destroyed.

<a name="Trackable"></a>
## Trackable

***Trackable*** tokens allow an *observer* to detect that a linked object managed by an *owner* was destroyed. *Trackable* *observer* can not be *dangling* but can be *expired*. *Trackable* tokens can be implemented by reference counting, garbage collection or other technics.

<a name="Untrackable"></a>
## Untrackable

***Untrackable*** tokens do not allow an *observer* to detect that a linked object was destroyed. *Untrackable* *observer* may be *dangling*. *Untrackable* tokens usually implemented by raw pointers.

<a name="Basis"></a>
# Basis

Tokens are grouped in bases according to common characteristics, such as *trackable*, *untrackable*, *raw* and so on. By default, tokens from the `safe` basis are imported in the `otn` namespace.

<a name="Safe"></a>
## Safe

Tokens in the `safe` basis are *trackable*, can not be *dangling* and implements RAII idiom. Tokens are **safe only in object's lifetime semantics**, not thread-safe or some other safety.

|`otn::safe`|implemented by|
|---|---|
|`unique[_single]<T>`|`std::shared_ptr<T>`|
|`unique_optional<T>`|`std::shared_ptr<T>`|
|`shared[_single]<T>`|`std::shared_ptr<T>`|
|`shared_optional<T>`|`std::shared_ptr<T>`|
|`weak_optional<T>`|`std::weak_ptr<T>`|
|`unified[_single]<T>`|`std::shared_ptr<T>`|
|`unified_optional<T>`|`std::shared_ptr<T>`|

<a name="SafeWeak"></a>
The main difference of the `safe::unique`, `safe::shared`, `safe::weak` from the `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr` that it is possible to create the `safe::weak` both from the `safe::unique` and the `safe::shared`, while the `std::weak_ptr` can be created only from the `std::shared_ptr` and the `std::unique_ptr` does not have *trackable* *weak* counterpart.

The `safe::unified` can be created from any another `safe` token.

<p>
<details>
<summary>Example</summary>

```c++
#include <otn/all.hpp>
#include <iostream>

void print(const std::string& caption,
           const otn::unified_optional<int>& token)
{
    std::cout << caption;

    if (token)
        std::cout << *token;
    else
        std::cout << "empty";

    std::cout << std::endl;
}

int main()
{
    using namespace otn;

    unique_optional<int> a{itself, 6};
    shared_optional<int> b{itself, 7};
    weak_optional<int>   weak_a = a;
    weak_optional<int>   weak_b = b;

    print("        unique: ", a);
    print("weak -> unique: ", weak_a);
    print("        shared: ", b);
    print("weak -> shared: ", weak_b);

    std::cout << "clear tokens" << std::endl;
    utilize(std::move(a));
    utilize(std::move(b));

    print("        unique: ", a);
    print("weak -> unique: ", weak_a);
    print("        shared: ", b);
    print("weak -> shared: ", weak_b);
}
```

Output:

```
        unique: 6
weak -> unique: 6
        shared: 7
weak -> shared: 7
clear tokens
        unique: empty
weak -> unique: empty
        shared: empty
weak -> shared: empty
```

</details>
</p>

<a name="SafeUnified"></a>
The `safe::unified` is an **owner**. It can lock and prolong an object's lifetime managed both the `safe::shared` and `safe::unique` in the same way as the `std::weak_ptr::lock()` for the `std::shared_ptr`. During this period, an object is under shared ownership, even if it initially owned by `safe::unique`. An object under the `safe::unique` management (as well as under the `safe::shared`) may be destroyed not in the `safe::unique` destructor immediately, it may be destroyed later in the `safe::unified` destructor if it was locked by `safe::unified` in another thread. Therefore, **try to lock an object's lifetime and access an object by the `safe::unified` as short as possible**.

<p>
<details>
<summary>Example</summary>

```c++
#include <otn/all.hpp>
#include <iostream>

void consumeUnique(otn::unique_optional<std::string> unique_string)
{
    if (unique_string)
    {
        std::cout << "Consume the unique string: " << *unique_string << std::endl;
        otn::utilize(std::move(unique_string));
    }

    assert(!unique_string);
}

int main()
{
    using namespace std;
    using namespace otn;

    // Actually, the `hello_unique` and the `hello_weak` should be a data members of a classes.
    unique_optional<string> hello_unique{itself, "Hello, World!"};
    weak_optional<string>   hello_weak = hello_unique;

    cout << "Initial unique string: " << *hello_unique << endl;

    {
        // Prolong the lifetime of the string from the hello_unique in this scope.
        unified_optional<string> hello_unified = hello_weak;

        consumeUnique(std::move(hello_unique));

        assert(!hello_unique);
        assert(hello_unified);
        assert(!hello_weak.expired());

        cout << "The unique string is empty." << endl;
        access(hello_weak, [](const auto& hello_weak)
        {
            cout << "But the weak string is still alive: "
                 << hello_weak << endl;
        });
    }

    assert(hello_weak.expired());
    cout << "And here the weak string has expired." << endl;
}
```

Output:

```
Initial unique string: Hello, World!
Consume the unique string: Hello, World!
The unique string is empty.
But the weak string is still alive: Hello, World!
And here the weak string has expired.
```

</details>
</p>

Tokens from the `safe` basis are imported in the `otn` namespace by default. For example, there is no need to write `otn::safe::unique<Foo>` explicit, `otn::unique<Foo>` is enough.

<a name="Slim"></a>
## Slim

The `slim` basis contains *untrackable* lightweight tokens with RAII idiom and minimum runtime overhead.

|`otn::slim`|implemented by|
|---|---|
|`unique[_single]<T, D>`|`std::unique_ptr<T, D>`|
|`unique_optional<T, D>`|`std::unique_ptr<T, D>`|

The `slim::unique` is the analog of the `std::unique_ptr`, which can be `optional` and `single`.

<a name="Raw"></a>
## Raw

Tokens in the `raw` basis are low-level, observers are without RAII idiom, *untrackable* and can be *dangling*.

|`otn::raw`|implemented by|
|---|---|
|`unique[_single]<T>`|`T`|
|`unique_optional<T>`|`std::optional<T>`|
|`weak[_single]<T>`|`T*`|
|`weak_optional<T>`|`T*`|
|`unified[_single]<T>`|`T*`|
|`unified_optional<T>`|`T*`|

`raw::unique` tokens are wrappers over raw C++ objects with `automatic` [storage duration](https://en.cppreference.com/w/cpp/language/storage_duration#Storage_duration). They are introduced to provide unified representation and access to raw C++ objects with other tokens. They simplify refactoring when the storage duration of an object changes (`automatic` <-> `dynamic`) in a variable or a data member of a class. Moving `raw::unique` tokens invalidate observers to them:

```c++
otn::raw::unique<some> a{otn::itself};
otn::raw::weak<some>   w = a;
otn::raw::unique<some> b{std::move(a)}; // Invalidates the 'w'.
// The 'w' observes the moved-from object 'a'.
```

**It is the responsibility of a developer to ensure that `raw::unique` tokens do not have observers before moving or manually update observers after moving**.

The `raw::unified` and `raw::weak` are wrappers over raw C++ pointers. They are represented to explicitly express `single` and `optional` multiplicity because the raw pointer `T*` is not `single` (it can be `nullptr`) nor `optional` (after move operation it is not "empty").

It is unlikely, but possible to create a smart pointer from a raw pointer given from another smart pointer:

```c++
auto a = std::make_unique<int>(7);
int* p = a.get();
std::unique_ptr<int> b{p}; // Compiles.
std::shared_ptr<int> c{p}; // Compiles.
```

Tokens from the `raw` basis can mitigate such situations:

```c++
auto a = std::make_unique<int>(7);
otn::raw::weak<int>    w = a;
std::unique_ptr<int>   b{w}; // Not compiles.
std::shared_ptr<int>   c{w}; // Not Compiles.
otn::unique<int>       d{w}; // Not compiles.
otn::slim::unique<int> e{w}; // Not compiles.
```

`raw` observers are *untrackable* and can be *dangling* if a linked object is destroyed. **It is the responsibility of a developer to ensure that the object's lifetime is longer than the lifetime of the `raw` observer**.
