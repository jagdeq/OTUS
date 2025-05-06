#ifndef ASYNC_H
#define ASYNC_H

#include <cstddef>

namespace async {
extern "C" size_t connect(size_t block_size);
extern "C" void disconnect(size_t context);
extern "C" void receive(const char* buffer, size_t buf_size, size_t context);
} // namespace async

#endif // ASYNC_H
