#pragma once
#include <iostream>
#include <string>
#include <string_view>

/**
 *  Public interface,
 *  assertion-like macro.
 */
#define ENSURE(cond, reason)                                \
    ::test::impl::ensure(                                   \
        (cond), (#cond), (reason), (__PRETTY_FUNCTION__),   \
        (__FILE__), (__LINE__))



/**
 *  Impl.
 */
namespace test::impl
{
//* Helper class tasked with outputting text and counting
struct Statistics
{
    static inline auto tests_passed = 0ULL;
    static inline auto tests_failed = 0ULL;
    static inline bool fail_mode    = false;

    ~Statistics()
    {
        std::cout
            << "\n"
            << "Tests total: " << (tests_failed + tests_passed) << "\n"
            << "     passed: " << tests_passed << "\n"
            << "     failed: " << tests_failed << "\n";
        tests_passed = 0;
        tests_failed = 0;
    }


    void pass(const char* reason) const noexcept
    {
        tests_passed++;
        fail_mode = false;
        std::cout << "test passed: " << reason  << "\n";
    }


    void fail(
        const char* cond_str,
        const char* reason,
        const char* func,
        const char* file,
        const int   line
    )const noexcept
    {
        tests_failed++;

        if (!fail_mode) {
            fail_mode = true;
            std::cout << "\n";
        }

        std::cout
            << "test FAILED: " << reason << "\n"
            << "  (" << cond_str << ")\n"
            << "in " << file << ":" << std::to_string(line) << "\n"
            << "     " << func << "\n\n"
        ;
    }

};



//* Unique instance of our statistics helper
inline Statistics statistics;



struct Test
{
    const bool      condition       = false;
    const char*     cond_str;
    const char*     reason;
    const char*     func;
    const char*     file;
    const int       line            = 0;



    Test() = default;


    constexpr Test(
        bool        condition_,
        const char* cond_str_,
        const char* reason_,
        const char* func_,
        const char* file_,
        const int   line_
    ) noexcept
        : condition {condition_}
        , cond_str  {cond_str_}
        , reason    {reason_}
        , func      {func_}
        , file      {file_}
        , line      {line_}
    {
    }



    operator bool() const noexcept
    {
        return condition;
    }



    Test const& operator()() const
    {
        if (condition)
            statistics.pass(reason);

        else
            statistics.fail(cond_str, reason, func, file, line);

        return *this;
    }



    Test then(Test&& test) const
    {
        if (condition)
            return test();

        else return Test{};
    }

};



//* The ENSURE macro expands to that
inline Test ensure(bool condition, const char* cond_str,
    const char* reason, const char* func, const char* file, int line)
{
    return Test{condition, cond_str, reason, func, file, line}();
}



} // namespace test::impl
