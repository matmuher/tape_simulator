#include <fstream>
#include <sstream>
#include <string>
#include <gtest/gtest.h>
#include <Sort.hpp>

void check_files(const std::string& f1, const std::string& f2)
{
    std::ifstream resf(f1);
    std::stringstream resb;
    resb << resf.rdbuf();

    std::ifstream ansf(f2);
    std::stringstream ansb;
    ansb << ansf.rdbuf();

    ASSERT_EQ(resb.str(), ansb.str());
}

// Demonstrate some basic assertions.
TEST(TestSort, Sort)
{
    int test_num = 3;

    for (int i = 1; i <= test_num; ++i)
    {
        std::string res_name = "../tests/res/res" + std::to_string(i);
        std::string test_name = "../tests/test/test" + std::to_string(i);
        std::string ans_name = "../tests/ans/ans" + std::to_string(i);

        ts::launch_sort_tape(test_name, ans_name);

        check_files(res_name, ans_name);
    }
}
