## Minimalist test module

The sole feature provided by this module is the `EXPECT` assertion:

```cpp
EXPECT(condition, rationale);
```

Its purpose is to express intent and obtain feedback about the run-time
behaviour of the code.

A notable difference with the classic `assert` is that it will not terminate
the program when evaluating to false. Instead it will output useful feedback.

Another difference resides in the ability for this assertion to be
short-circuited.
In the following example, the second condition is evaluated only if the first
one is verified:

```cpp
EXPECT(condition1, "message1") && EXPECT(condition2, "message2");
```

An output is generated for successful tests too.
Test count is printed at the end of the program.
All output happens on `stdout`.


### Compilation

To use this module, please include the following file in your project:
```
test-tool.hpp
```

Compatibility notes:

This project needs at least C++17 because it uses static inline variables in
order to keep the source code in the header.
Porting to C++11 would only require defining those few variables in a source
file.


### Usage example:

You may compile and run the file `example.cpp`.

```
void test_array()
{
    auto array = Array(8);

    // short-circuit to avoid out-of-bound check
    EXPECT(array.size() == 8, "array size must be 8")
        && EXPECT(array[0] == 0, "array[0] must be 0 initialized");
}
```

These tests could fail for instance if the constructor `Array(8)` produces an
array of 1 element, in which case you'll see on `stdout` a message like the
following:

```
test FAILED: array size must be 8
condition:   array.size() == n
in file:     ./example.cpp:62
@ function:  void test_array(const Int_array_base&, int)
```

Otherwise if the tests succeed, this is the program output:
```
test passed: array size must be 8
test passed: array[0] must be 0 initialized
```

In both cases a count of the tests is printed at the end of the program.
```
--Tests--
 passed:     2
 failed:     0
 total:      2
```
