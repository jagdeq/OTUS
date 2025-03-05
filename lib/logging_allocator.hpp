#ifndef LOGGING_ALLOCATOR_HPP
#define LOGGINH_ALLOCATOR_HPP

#include <cstdint>
#include <iostream>

#include "unused.hpp"

namespace cstm {
template <class T>
struct LoggingAllocator
{
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;

    LoggingAllocator() noexcept { std::cout << "default constr\n"; }

    template <class U>
    LoggingAllocator(const LoggingAllocator<U>&) noexcept
    {}

    pointer allocate(size_t n)
    {
        std::cout << "allocate: " << n << " elements\n";
        return static_cast<pointer>(::operator new(n * sizeof(T)));
    }

    void deallocate(pointer p, size_t n)
    {
        UNUSED(n);

        std::cout << (*(reinterpret_cast<uint32_t*>(p) - 1)) << std::endl;
        std::cout << "deallocate: " << n << " elements\n";
        ::operator delete(p);
    }

    template <class Up, class... Args>
    void construct(Up* p, Args&&... args)
    {
        std::cout << "construct\n";
        ::new ((void*)p) Up(std::forward<Args>(args)...);
    }

    void destroy(pointer p)
    {
        std::cout << "destroy\n";
        p->~T();
    }

    template <class U>
    struct rebind
    {
        using other = LoggingAllocator<U>;
    };
};
} // namespace cstm

#endif // LOGGING_ALLOCATOR_HPP
