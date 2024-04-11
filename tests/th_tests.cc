#include <gtest/gtest.h>

// Demonstrate some basic assertions.

TEST(thTest, name)
{
    EXPECT_EQ(name_test(), EXIT_SUCCESS);
}
