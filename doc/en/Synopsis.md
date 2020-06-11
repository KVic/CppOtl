# Synopsis

The public interface of an ordinary `otn` token (in pseudocode).

`T` is the type of a linked object.

```c++
template <class T>
class token
{
public:
    // Destructor
    ~token() = default;

    // Default constructors
    constexpr token() noexcept requires is_optional;
    token() requires is_single = delete;
    
    // Nullptr constructors
    constexpr token(std::nullptr_t) noexcept requires is_optional;
    token(std::nullptr_t) requires is_single = delete;
    
    // Itself constructors
    template <class ... Args>
    explicit token(itself_t, Args&& ... args) requires itself_construction_enabled;
    template <class Y, class ... Args>
    explicit token(itself_type_t<Y>, Args&& ... args) requires itself_construction_enabled;
    
    // Copy constructor
    token(const token& other) noexcept(depends);
    
    // Move constructor
    token(token&& other) noexcept(depends);
    
    // Forwarding constructors
    template <class Token> requires construction_implicit_enabled_from<Token>
    token(Token&& other) noexcept(depends);
    template <class Token> requires construction_explicit_enabled_from<Token>
    explicit token(Token&& other) noexcept(depends);
    
    // Copy nullptr assignment operator
    token& operator=(std::nullptr_t) noexcept requires is_optional;
    
    // Copy assignment operator
    token& operator=(const token& other) noexcept(depends);
    
    // Move assignment operator
    token& operator=(token&& other) noexcept(depends);
    
    // Forwarding assignment operators
    template <class Token> requires construction_implicit_enabled_from<Token>
    token& operator=(Token&& other) noexcept(depends);
    
    // Copy conversion functions
    template <class Token> requires copy_convertion_implicit_to<Token>
    operator Token() const & noexcept(depends);
    template <class Token> requires copy_convertion_explicit_to<Token>
    explicit operator Token() const & noexcept(depends);

    // Move conversion functions
    template <class Token> requires move_convertion_implicit_to<Token>
    operator Token() const && noexcept(depends);
    template <class Token> requires move_convertion_explicit_to<Token>
    explicit operator Token() const && noexcept(depends);
    
    // Observers
    T& operator*() const noexcept requires dereferencing_enabled;
    T* operator->() const noexcept requires dereferencing_enabled;
    explicit operator bool() const noexcept requires direct_access_enabled;
    bool expired() const noexcept requires is_observer && is_trackable;
    template <class Token> requires has_same_owner_base<Token>
    bool owner_before(const Token& other) const noexcept;
};
```

#### Non-member functions

```c++
template <class Token>
void std::swap(Token& a, Token& b) noexcept;
template <class TokenT, class TokenU>
bool operator==,!=,<,<=,>,>=(const TokenT& a, const TokenU& b) noexcept;

template <class T, class ... Args>
safe::unique_single<T> safe::make_unique(Args&& ... args);
template <class T, class ... Args>
safe::shared_single<T> safe::make_shared(Args&& ... args);
template <class T, class ... Args>
slim::unique_single<T> slim::make_unique(Args&& ... args);
template <class T, class ... Args>
raw::unique_single<T> raw::make_unique(Args&& ... args);
```

#### Helper classes

```c++
template <class Token>
struct std::hash<Token>;
```

#### Generic token

```c++
otn::generic::token<Element, Basis, Ownership, Multiplicity, Deleter>;
```

Returns the type of a token if `generic::token<...>` is valid with given parameters, otherwise returns `void`.
