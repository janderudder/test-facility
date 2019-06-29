## Minimalist test facility.

This test tool uses inline static variables, so needs at least C++17
to compile.


#### Usage example:

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
