## Minimalist test module

The sole feature provided by this module is the an assertion.

```cpp
ENSURE(condition, rationale);
```

Its purpose is to express intent and obtain feedback about the behaviour of
the code.

One difference with classic `assert` is that it will not kill the program on
first error, and give useful feedback.

The second difference is that you can short-circuit these assertions.
In the following example, the second assertion is evaluated only if the first
test succeeds:

```cpp
ENSURE(cond1, "message1") && ENSURE(cond2, "message2");
```

Another difference is that a line will be output for each successful test.


### Compilation

Just include the following files in your project:
```
util/invoke.hpp
test-tool.hpp
```
Needs at least C++17 because of static inline variables (easily portable to C++11).


### Usage example:

```
void test_array()
{
    auto array = Array(8);
    ENSURE(array.size() == 1, "array size must be 1");
    && ENSURE(array[0] == 8, "array[0] must be 8");   // short-circuit to avoid out-of-bound check
}
```

These tests could fail for instance if `new Array(8)` produces an array of
8 elements, in which case you'll get the following message on `stdout`:

```
test FAILED: array size must be 1
  (array.size() == 1)
in ./main.cpp:42
   void test_array()
```
