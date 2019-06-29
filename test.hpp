/**
 *  Minimalist test facility
 *
 *  Usage example:
 *  ```
 *      void test_array() {
 *          auto array = Array(8);
 *          ENSURE(array.size() == 1, "array size must be 1");
 *          ENSURE(array[0] == 8, "array[0] must be 8");
 *      }
 *  ```
 *
 *  These tests could fail for instance if `new Array(8)` produces an array of
 *  8 elements, in which case you'll get the following message on stdout:
 *  ```
 *      test failed for condition:
 *      `array.size() == 1`
 *      reason: "array size must be 1"
 *      in: `void test_array()`
 *      at ./example.cpp:3
 *  ```
 */
#pragma once
#include <any>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

/**
 *  Public test interface
 */
// Assertion macro, throw on failure
#define ENSURE(cond, reason) (::test::detail::__ensure( \
        (cond),                                         \
        (#cond),                                        \
        (reason),                                       \
        (__PRETTY_FUNCTION__),                          \
        (__FILE__),                                     \
        (__LINE__)                                      \
    ))


#if 0
// Output error if any, resume execution
#define TEST(cond, reason) (::test::detail::test(       \
        (cond),                                         \
        (#cond),                                        \
        (reason),                                       \
        (__PRETTY_FUNCTION__),                          \
        (__FILE__),                                     \
        (__LINE__)                                      \
    ))
#endif

/**
 *  Public scoped test interface
 */
namespace test
{

}


namespace test::detail
{

// Default test output function
const auto default_out_fn = [](std::string_view sv)
{
    std::cout << sv.data();
};


// Global output function object
static inline std::any out_fn = default_out_fn;


static inline void outf(std::initializer_list<std::string_view> const sv_list)
{
    for (const auto& sv : sv_list) {
        std::invoke(std::any_cast<decltype(default_out_fn)>(out_fn), sv);
    }
}


// Class template for custom out_fn
template <class Fn>
struct Custom_Out_Fn
{
    Fn out_fn;

    template <class T>
    void operator()(const T& str) {
        this->out_fn(str);
    }
};


// Initialize function object
template <class Fn>
void __init_out_fn(Fn&& out_fn)
{
    out_fn = Custom_Out_Fn{std::move(out_fn)};
}


// Exception to indicate failed test
struct Test_Failure : public std::runtime_error
{
    explicit Test_Failure(std::string_view message) noexcept
        : std::runtime_error(message.data())
    {}
};


// Macro ENSURE expands to this
inline void __ensure(
    bool                condition,
    std::string_view    cond_str,
    std::string_view    reason,
    std::string_view    func,
    std::string_view    file,
    int                 line    )
{
    using namespace std::string_literals;

    if (!condition)
    {
        throw Test_Failure {
            "\"Ensure\" test failed for condition:\n"s
            + "`" + std::string{cond_str}   + "`\n"
            + "reason: \""  + reason.data() + "\"\n"
            + "in: `"       + func.data()   + "`\n"
            + "at "         + file.data()   + ":" + std::to_string(line) + "\n"
        };
    }
    else
    {
        outf({"Test passed:\n", "Hello", "world!"});
        // outf("Ensure ( ");
    }
}


} // namespace test::detail
