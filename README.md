## Minimalist test facility.

#### Usage example:

```
void test_array() {
    auto *array = new Array(8);
    ENSURE(array.size() == 1, "array size must be 1");
    ENSURE(array[0] == 8, "array[0] must be 8");
}
```

These tests could fail for instance if `new Array(8)` produces an array of
8 elements, in which case you'll get the following message on `stdout`:

```
test failed for condition:
`array.size() == 8`
reason: "array size must be 1"
in: `void test_array()`
at ./example.cpp:3
```
