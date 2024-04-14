#include <gtest/gtest.h>
#include <my_tests.hpp>
// Demonstrate some basic assertions.

TEST(thTest, name)
{
    EXPECT_EQ(test_file01(), EXIT_SUCCESS);
}
