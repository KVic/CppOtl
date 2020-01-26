# Construction

Constructing `otn` tokens is similar to constructing [smart pointers](https://en.cppreference.com/w/cpp/memory) from the C++ STL.

See the [Synopsis](Synopsis.md) for token's constructors and factory functions.

## Itself constructors

<a name="itself_constructor"></a>
### `itself` constructor

```c++
template <class ... Args>
explicit token(itself_t, Args&& ... args);
```

Constructs a `token<T>` that creates an object of type `T`, initialized as if direct-initializing from the arguments `std::forward<Args>(args)...`.


##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

class Foo
{
public:
    explicit Foo(int value) : m_value{value} {}
    int value() const { return m_value; }

private:
    int m_value;
};

int main()
{
    using namespace otn;

    // Constructing a, b and c are equivalent.
    unique<Foo> a{itself, 7};
    unique<Foo> b{new Foo(7)};
    auto c = make_unique<Foo>(7);

    std::cout << "a: " << (*a).value() << std::endl;
    std::cout << "b: " << (*b).value() << std::endl;
    std::cout << "c: " << (*c).value() << std::endl;
}
```

Output:

```
a: 7
b: 7
c: 7
```

### `itself_type` constructor

```c++
template <class Y, class ... Args>
explicit token(itself_type_t<Y>, Args&& ... args);
```

Constructs a `token<T>` that creates an object of type `Y`, initialized as if direct-initializing from the arguments `std::forward<Args>(args)...`.

##### Example

```c++
#include <otn/all.hpp>
#include <iostream>

class Foo
{
public:
    virtual int value() const = 0;

    virtual ~Foo() = default;
};

class Bar : public Foo
{
public:
    explicit Bar(int value) : m_value{value} {}
    int value() const override { return m_value; }

private:
    int m_value;
};

int main()
{
    using namespace otn;

    // Constructing a, b and c are equivalent.
    unique<Foo> a{itself_type<Bar>, 7};
    unique<Foo> b{new Bar(7)};
    unique<Foo> c = make_unique<Bar>(7);

    std::cout << "a: " << (*a).value() << std::endl;
    std::cout << "b: " << (*b).value() << std::endl;
    std::cout << "c: " << (*c).value() << std::endl;
}
```

Output:

```
a: 7
b: 7
c: 7
```
