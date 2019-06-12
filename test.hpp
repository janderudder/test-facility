/**
 *  Minimalist test facility.
 *
 *  Usage example:
 *  ```
 *      void test_array() {
 *          auto *array = new Array(8);
 *          ENSURE(array.size() == 1, "array size must be 1");
 *          ENSURE(array[0] == 8, "array[0] must be 8");
 *      }
 *  ```
 *
 *  These tests could fail for instance if `new Array(8)` produces an array of
 *  8 elements, in which case you'll get the following message on stdout:
 *  ```
 *      test failed for condition:
 *      `array.size() == 8`
 *      reason: "array size must be 1"
 *      in: `void test_array()`
 *      at ./example.cpp:3
 *  ```
 */
#pragma once
#include <stdexcept>
#include <string>
#include <string_view>

// Assertion macro to use as tests
#define ENSURE(cond, reason) ::test::detail::ensure__(  \
    (cond), (#cond), (reason), (__PRETTY_FUNCTION__),   \
    (__FILE__), (__LINE__))


namespace test::detail
{

// Exception to indicate failed test
struct Test_Failure : public std::runtime_error
{
    explicit Test_Failure(std::string_view message) noexcept
        : std::runtime_error(message.data())
    {}
};


// Macro ENSURE expands to this
inline void ensure__(bool condition, const char* cond_str,
    const char* reason, const char* func, const char* file, int line)
{
    if (!condition)
    {
        throw Test_Failure(
            "test failed for condition:\n`"
            + std::string{cond_str}
            + "`\nreason: \"" + reason
            + "\"\nin: `" + func
            + "`\nat " + file + ":" + std::to_string(line)
            + "\n"
        );
    }
}


} // namespace test::detail
