# UML relations

## Property

`otn` tokens can express the *aggregation kind* and the *multiplicity range* of a *Property* (see *"9.5 Properties"* in [UML 2.5.1](https://www.omg.org/spec/UML/2.5.1/PDF)) and can represent a *memberEnd* of an *Association* as a data member of a class in C++ code.

| UML AggregationKind | otn::ownership |
|-----------------|-----------|
| `none`          | `weak`    |
| `shared`        | `shared`  |
| `composite`     | `unique`  |

See [Ownership](Characteristics.md#Ownership) for details.

| UML multiplicity range | otn::multiplicity |
|----------|------------|
| `[0..1]` | `optional` |
| `[1..1]` | `single`   |

See [Multiplicity](Characteristics.md#Multiplicity) for details.

## Parameter and Variable

`otn` tokens can represent *Parameters* (see “9.4.3.4 Parameters”) and *Variables* (see “15.2.3.5 Variables”) as parameters of a function or variables in C++ code.

See [Ownership](Characteristics.md#Ownership) for details.

## Example

See the [Car](https://gitlab.com/CppObjectTokens/Module/Example/Car) example that demonstrates UML vs C++ relations.
