#ifndef CUSTOM_ALLOCATOR_HPP
#define CUSTOM_ALLOCATOR_HPP

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include "unused.hpp"

constexpr size_t g_chunkSize = 20;

namespace cstm {
template <class T, size_t chunkSize = g_chunkSize>
struct ReserveAllocator
{
    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = const T*;
    using reference       = T&;
    using const_reference = const T&;

    ReserveAllocator() noexcept
        : m_allocatedElements{0}
    {
        m_buffer.reserve(chunkSize);
    }

    template <class U>
    ReserveAllocator(const ReserveAllocator<U>&) noexcept
    {}

    pointer allocate(size_t n)
    {
        if (n != 1)
            return static_cast<pointer>(::operator new(n * sizeof(T)));
        else {
            if (m_allocatedElements == 0 || (m_allocatedElements % chunkSize == 0))
                for (size_t i = 0; i != chunkSize; ++i)
                    m_buffer.emplace_back(static_cast<pointer>(::operator new(sizeof(T))));

            m_allocatedElements++;
            return m_buffer[m_allocatedElements - 1];
        }
    }

    void deallocate(pointer p, size_t n)
    {
        if (n != 1)
            ::operator delete(p);
        else {
            auto it = std::find(m_buffer.begin(), m_buffer.end(), p);
            ::operator delete(*it);
        }
    }

    template <class Up, class... Args>
    void construct(Up* p, Args&&... args)
    {
        ::new ((void*)p) Up(std::forward<Args>(args)...);
    }

    void destroy(pointer p) { p->~T(); }

    template <class U>
    struct rebind
    {
        using other = ReserveAllocator<U, chunkSize>;
    };

private:
    size_t m_allocatedElements;
    std::vector<pointer> m_buffer;
};
} // namespace cstm

#endif // CUSTOM_ALLOCATOR_HPP
