# Access

Access to an object of a token is available by the following methods.

1. [One token](#One_token)
   1. [Single](#One_Single)
   1. [Optional](#One_Optional)
      1. [Classic "if-else"](#One_Classic_if_else)
         1. [Dereferenceable](#One_Dereferenceable)
         1. [Proxy accessible](#One_Proxy_accessible)
      1. [Unified "if-else"](#One_Unified_if_else)
      1. [Unified lambda](#One_Unified_lambda)
      1. [Range-based "for"](#One_Range_based_for)
1. [Several tokens](#Several_tokens)
   1. [Single](#Several_Single)
   1. [Optional](#Several_Optional)
      1. [Classic "if-else"](#Several_Classic_if_else)
         1. [Dereferenceable](#Several_Dereferenceable)
         1. [Proxy accessible](#Several_Proxy_accessible)
      1. [Unified "if-else"](#Several_Unified_if_else)
      1. [Unified lambda](#Several_Unified_lambda)

**Note:** **Prefer to use the `operator*()` rather than the `operator->()` of an `otn` token**, since it is designed as an *object token* not as a *pointer to an object at some address*. The `operator->()` may be deprecated and removed in the future.

<a name="One_token"></a>
## One token

<a name="One_Single"></a>
### Single

A `single` token must always refer to an object, there is **no need to check** it, it can be accessed directly.

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class Single>
void print(const Single& token)
{
    std::cout << "object: " << *token << std::endl;
}

int main()
{
    using namespace otn;

    unique<int>    a{itself, 7};
    raw::weak<int> b = a;

    print(a);
    print(b);
}
```
Output:

```
object: 7
object: 7
```

<a name="One_Optional"></a>
### Optional

An `optional` token may be empty, it **must be checked** before accessing.

<a name="One_Classic_if_else"></a>
### Classic "if-else"

<a name="One_Dereferenceable"></a>
#### Dereferenceable

A dereferenceable token can be accessed directly, after check. This method does not work with non-dereferenceable tokens.

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class Optional>
void print(const Optional& token)
{
    if (token)
        std::cout << "object: " << *token << std::endl;
    else
        std::cout << "token is empty" << std::endl;
}

int main()
{
    using namespace otn;

    unique_optional<int>    a{itself, 7};
    weak_optional<int>      b = a;
    raw::weak_optional<int> c = a;
    raw::weak_optional<int> d;

    print(a);
    // print(b); // Error: the safe::weak_optional is not dereferenceable.
    print(c);
    print(d);
}
```

Output:

```
object: 7
object: 7
token is empty
```

<a name="One_Proxy_accessible"></a>
#### Proxy accessible

Some tokens are not dereferenceable (`safe::weak_optional`, `std::weak_ptr`). Such tokens can be accessed by a proxy.

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class ProxyAccessible>
void print(const ProxyAccessible& token)
{
    if (otn::unified_optional<int> loc = token)
        std::cout << "object: " << *loc << std::endl;
    else
        std::cout << "token is empty" << std::endl;
}

int main()
{
    using namespace otn;

    unique_optional<int> a{itself, 7};
    weak_optional<int>   b = a;
    weak_optional<int>   c;

    print(b);
    print(c);
}
```

Output:

```
object: 7
token is empty
```

<a name="One_Unified_if_else"></a>
### Unified "if-else"

The `otn::gain` function provides unified optimized access to any token type. It returns a list of a proxy, which can be bound to variables by *structured binding*, after check. A list with one proxy can be dereferenced directly, after check.

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class Optional>
void print(const Optional& token)
{
    if (auto loc = otn::gain(token))
        std::cout << "object: " << *loc << std::endl;
    else
        std::cout << "token is empty" << std::endl;
}

int main()
{
    using namespace otn;

    unique_optional<int>    a{itself, 7};
    weak_optional<int>      b = a;
    raw::weak_optional<int> c = a;
    raw::weak_optional<int> d;

    print(a);
    print(b);
    print(c);
    print(d);
}
```

Output:

```
object: 7
object: 7
object: 7
token is empty
```

<a name="One_Unified_lambda"></a>
### Unified lambda

The `otn::access` function provides unified optimized access to any token type. It checks tokens and passes they object references to the lambda.

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class Optional>
void print(const Optional& token)
{
    otn::access(token, [](auto& object)
    { std::cout << "object: " << object << std::endl; },
    [] // else
    { std::cout << "token is empty" << std::endl; });
}

int main()
{
    using namespace otn;

    unique_optional<int>    a{itself, 7};
    weak_optional<int>      b = a;
    raw::weak_optional<int> c = a;
    raw::weak_optional<int> d;

    print(a);
    print(b);
    print(c);
    print(d);
}
```

Output:

```
object: 7
object: 7
object: 7
token is empty
```

<a name="One_Range_based_for"></a>
### Range-based "for"

`otn` tokens meet the requirements of `std::ranges::range`, they can be accessed by *range-based for* loop.

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class Token>
void print(const Token& token)
{
    for (auto& token : token)
        std::cout << "object: " << *token << std::endl;
}

int main()
{
    using namespace otn;

    unique_single<int>      a{itself, 7};
    weak_optional<int>      b = a;
    raw::weak_single<int>   c = a;
    raw::weak_optional<int> d;

    print(a);
    print(b);
    print(c);
    print(d);
}
```

Output:

```
object: 7
object: 7
object: 7
```

<a name="Several_tokens"></a>
## Several tokens

<a name="Several_Single"></a>
### Single

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class SingleA, class SingleB>
void calc(const SingleA& a, const SingleB& b)
{
    std::cout << "result: " << *a + *b << std::endl;
}

int main()
{
    using namespace otn;

    unique<int>    a{itself, 7};
    shared<int>    b{itself, 3};
    raw::weak<int> c = a;

    calc(a, b);
    calc(b, c);
}
```

Output:

```
result: 10
result: 10
```


<a name="Several_Optional"></a>
### Optional

<a name="Several_Classic_if_else"></a>
### Classic "if-else"

<a name="Several_Dereferenceable"></a>
#### Dereferenceable

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class OptionalA, class OptionalB>
void calc(const OptionalA& a, const OptionalB& b)
{
    if (a && b)
        std::cout << "result: " << *a + *b << std::endl;
    else
        std::cout << "invalid arguments" << std::endl;
}

int main()
{
    using namespace otn;

    unique_optional<int>    a{itself, 7};
    shared_optional<int>    b{itself, 3};
    weak_optional<int>      c = a;
    raw::weak_optional<int> d = a;
    raw::weak_optional<int> e;

    calc(a, b);
    // calc(b, c); // Error: the safe::weak_optional is not dereferenceable.
    calc(d, e);
}
```

Output:

```
result: 10
invalid arguments
```

<a name="Several_Proxy_accessible"></a>
#### Proxy accessible

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class ProxyAccessibleA, class ProxyAccessibleB>
void calc(const ProxyAccessibleA& a, const ProxyAccessibleB& b)
{
    if (otn::unified_optional<int> loc_a = a)
        if (otn::unified_optional<int> loc_b = b)
        {
            std::cout << "result: " << *loc_a + *loc_b << std::endl;
            return;
        }

    std::cout << "invalid arguments" << std::endl;
}

int main()
{
    using namespace otn;

    unique_optional<int> a{itself, 7};
    shared_optional<int> b{itself, 3};
    weak_optional<int>   c = a;
    weak_optional<int>   d = b;
    weak_optional<int>   e;

    calc(c, d);
    calc(d, e);
}
```

Output:

```
result: 10
invalid arguments
```

<a name="Several_Unified_if_else"></a>
### Unified "if-else"

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class OptionalA, class OptionalB>
void calc(const OptionalA& a, const OptionalB& b)
{
    if (auto locs = otn::gain(a, b))
    {
        auto& [a, b] = locs;
        std::cout << "result: " << a + b << std::endl;
    }
    else
    {
        std::cout << "invalid arguments" << std::endl;
    }
}

int main()
{
    using namespace otn;

    unique_optional<int>    a{itself, 7};
    shared_optional<int>    b{itself, 3};
    weak_optional<int>      c = a;
    raw::weak_optional<int> d = a;
    raw::weak_optional<int> e;

    calc(a, b);
    calc(b, c);
    calc(d, e);
}
```

Output:

```
result: 10
result: 10
invalid arguments
```

<a name="Several_Unified_lambda"></a>
### Unified lambda

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

template <class OptionalA, class OptionalB>
void calc(const OptionalA& a, const OptionalB& b)
{
    otn::access(a, b, [](auto& a, auto& b)
    {
        std::cout << "result: " << a + b << std::endl;
    },
    [] // else
    {
        std::cout << "invalid arguments" << std::endl;
    });
}

int main()
{
    using namespace otn;

    unique_optional<int>    a{itself, 7};
    shared_optional<int>    b{itself, 3};
    weak_optional<int>      c = a;
    raw::weak_optional<int> d = a;
    raw::weak_optional<int> e;

    calc(a, b);
    calc(b, c);
    calc(d, e);
}
```

Output:

```
result: 10
result: 10
invalid arguments
```
