#include <gtest/gtest.h>

#include "async.h"

// TEST(async_test, invalid_context_disconnect)
// {
//     try {
//         async::disconnect(1);
//     } catch (std::exception& ex) {
//         ASSERT_STREQ("Invalid context", ex.what());
//     }
// }

// TEST(async_test, invalid_context_receive)
// {
//     std::string cmd{"cmd1"};

//     try {
//         async::receive(cmd.data(), cmd.size(), 1);
//     } catch (std::exception& ex) {
//         ASSERT_STREQ("Invalid context", ex.what());
//     }
// }

TEST(async_test, invalid_block_size)
{
    try {
        async::connect(0);
    } catch (std::exception& ex) {
        ASSERT_STREQ("Invalid block size", ex.what());
    }
}

TEST(async_test, invalid_buffer_ptr)
{
    try {
        async::receive(nullptr, 1, 0);
    } catch (std::exception& ex) {
        ASSERT_STREQ("Invalid buffer pointer", ex.what());
    }
}

TEST(async_test, invalid_buffer_size)
{
    std::string cmd{"cmd1"};

    try {
        async::receive(cmd.data(), 0, 0);
    } catch (std::exception& ex) {
        ASSERT_STREQ("Invalid buffer size", ex.what());
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
