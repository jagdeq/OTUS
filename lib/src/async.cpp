#include "async.h"

#include <sstream>

#include "async_interface.hpp"

size_t async::connect(size_t block_size)
{
    if (block_size == 0)
        throw std::invalid_argument("Invalid block size");

    return async::IAsync::getInstance().connect(block_size);
}

void async::disconnect(size_t context) { async::IAsync::getInstance().disconnect(context); }

void async::receive(const char* buffer, size_t buf_size, size_t context)
{
    if (buffer == nullptr)
        throw std::invalid_argument("Invalid buffer pointer");

    std::vector<std::string> buf{std::string(buffer, buf_size)};
    async::IAsync::getInstance().receive(buf, context);
}
