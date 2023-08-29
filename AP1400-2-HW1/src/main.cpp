
#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

using Matrix = std::vector<std::vector<double>>;

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        std::cout << algebra::determinant(Matrix{{1, 2}, {3, 4}});
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}