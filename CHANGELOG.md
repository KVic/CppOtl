# Changelog

## 1.1.0

### General

* Disabled conversion from `unified` to `weak` ownership. `unified` ownership must be used in the same use cases as a regular C++ reference `&`.
* Refactored the proxy list returned by the `gain` function. It provides access to tokens and can be dereferenced to access tokens' objects.
* Added C++20 Concepts support in the implementation of tokens.

### Tokens

Added tokens:

* `raw`
  * `raw::unique[_single]<T>`
  * `raw::unique_optional<T>`

## 1.0.0

### General

Initial release.

### Tokens

Added tokens:

* `safe`
  * `safe::unique[_single]<T>`
  * `safe::unique_optional<T>`
  * `safe::shared[_single]<T>`
  * `safe::shared_optional<T>`
  * `safe::weak_optional<T>`
  * `safe::unified[_single]<T>`
  * `safe::unified_optional<T>`

* `slim`
  * `slim::unique[_single]<T, D>`
  * `slim::unique_optional<T, D>`

* `raw`
  * `raw::weak[_single]<T>`
  * `raw::weak_optional<T>`
  * `raw::unified[_single]<T>`
  * `raw::unified_optional<T>`
