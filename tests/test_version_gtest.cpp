#include <gtest/gtest.h>

#include "lib.hpp"

TEST(test_version, test_valid_version) { ASSERT_TRUE(version() > 0); }

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
