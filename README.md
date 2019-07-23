## Minimalist test module

The sole feature provided by this module is the `ENSURE` assertion:

```cpp
ENSURE(condition, rationale);
```

Its purpose is to express intent and obtain feedback about the run-time
behaviour of the code.

A notable difference with the classic `assert` is that it will not terminate
the program when evaluating to false. Instead it will output useful feedback.

Another difference resides in the ability for this assertions to be
short-circuited.
In the following example, the second condition is evaluated only if the first
one is verified:

```cpp
ENSURE(condition1, "message1") && ENSURE(condition2, "message2");
```

An output is generated for successful tests too.


### Compilation

To use this module, please include the following files in your project:
```
util/invoke.hpp
test-tool.hpp
```

Compatibility notes:

This project needs at least C++17 because of static inline variables.
Porting to C++11 would just require defining those few variables in a source file.

You may get rid of the custom "invoke.hpp" and replace it by the standard
`<functional>` header. Just update the inclusion in `test-tool.hpp`.

### Usage example:

```
void test_array()
{
    auto array = Array(8);
    ENSURE(array.size() == 1, "array size must be 1")
    && ENSURE(array[0] == 8, "array[0] must be 8");   // short-circuit to avoid out-of-bound check
}
```

These tests could fail for instance if the constructor `Array(8)` produces an
array of 8 elements, in which case you'll get the following message on `stdout`:

```
test FAILED: array size must be 1
  (array.size() == 1)
in ./main.cpp:42
     void test_array()
```

Otherwise, when the tests succeed, this is the program output:
```
test passed: array size must be 1
test passed: array[0] must be 8
```
