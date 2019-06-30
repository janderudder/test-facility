## Minimalist test facility.

The sole feature provided by this piece of code is the following macro:
```cpp
ENSURE(condition, rationale)
```
Its purpose is to express intent and obtain feedback about the behaviour of the code.


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
    ENSURE(array[0] == 8, "array[0] must be 8");
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
