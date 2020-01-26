# Traits

|Name|Description|
|----------|------------|
| `traits::element_t<Token>`| returns the type of the object of a `Token` |
| `traits::basis_t<Token>`| returns the basis of a `Token` |
| `traits::ownership_t<Token>`| returns the ownership of a `Token` |
| `traits::multiplicity_t<Token>`| returns the multiplicity of a `Token` |
| `traits::deleter_t<Token>`| returns the deleter of a `Token` |
| `traits::lifetime::role_v<Token>`| returns the lifetime role of a `Token` |
| --- |  |
| `element_is_v<Token, Element>`| checks if the type of the object of a `Token` is an `Element` |
| `basis_is_v<Token, Basis>`| checks if the basis of a `Token` is a `Basis` |
| `ownership_is_v<Token, Ownership>`| checks if the ownership of a `Token` is an `Ownership` |
| `multiplicity_is_v<Token, Multiplicity>`| checks if the multiplicity of a `Token` is a `Multiplicity` |
| `deleter_is_v<Token, Deleter>`| checks if the deleter of a `Token` is a `Deleter` |
| --- |  |
| `is_token_v<Token>`| checks if a `Token` is the `otn` token |
| `is_owner_v<Token>`| checks if a `Token` is the owner |
| `is_observer_v<Token>`| checks if a `Token` is the observer |
| `is_optional_v<Token>`| checks if a `Token` has the optional multiplicity |
| `is_single_v<Token>`| checks if a `Token` has the single multiplicity |
| --- |  |
| `is_trackable_v<Token>`| checks if a `Token` is trackable |
| `is_dereferenceable_v<Token>`| checks if a `Token` is dereferenceable |
| `is_direct_accessible_v<Token>`| checks if a `Token` is direct accessible |
| `is_proxy_accessible_v<Token>`| checks if a `Token` is accessible only by proxy |
| --- |  |
| `is_not_empty_v<Token>`| checks if a `Token` can not be empty |
| `is_maybe_empty_v<Token>`| checks if a `Token` may be empty or dangling |

## Example

See the [TraitPrinter](https://gitlab.com/CppObjectTokens/Module/Example/TraitPrinter) example.
