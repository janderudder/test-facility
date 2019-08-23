#include "test-tool.hpp"
#include <iostream>
#include <string>
#include <vector>

/**
 *  Testing material. Int_array_base have two children classes:
 *  one behaves as expected, the other does not.
 */
struct Int_array_base
{
    std::size_t         m_size;
    std::vector<int>    m_vec;

    Int_array_base(std::vector<int>&& vec)
        : m_size    {vec.size()}
        , m_vec     {std::move(vec)}
    {}

    int size() const {
        return m_size;
    }

    int const& operator[](int i) const {
        return m_vec[i];
    }

    int& operator[](int i) {
        return m_vec[i];
    }

};



struct Good_int_array   : public Int_array_base
{
    int m_size;

    Good_int_array(int sz) noexcept      // here int is used as vector size
        : Int_array_base {std::vector<int>(sz, 0)}
    {}
};



struct Bad_int_array    : public Int_array_base
{
    std::vector<int> m_vec;

    Bad_int_array(int i) noexcept      // vector will contain one int value
        : Int_array_base {std::vector<int>{i}}
    {}
};


/**
 *  Tests for our array types.
 */
void test_array(Int_array_base const& array, int n)
{
    ENSURE(array.size() == n, "array size must be " + std::to_string(n))
        && ENSURE(array[0] == 0, "array[0] must be 0");
}



int main()
{
    std::size_t n = 8;

    auto const good_array = Good_int_array(n);
    auto const bad_array = Bad_int_array(n);

    test_array(good_array, n);
    test_array(bad_array, n);

    // other examples
    ENSURE(true, "this passes");
    ENSURE(false, "this fails");

    // short-circuiting
    ENSURE(true, "doesn't fail")
        && ENSURE(false, "exec and fail")
        && ENSURE(true, "since previous failed, doesn't exec");

    ENSURE(true, "doesn't fail")
        || ENSURE(false, "doesn't fail")
        || ENSURE(true, "exec");

}
