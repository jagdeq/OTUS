#ifndef SOME_CONTAINER_HPP
#define SOME_CONTAINER_HPP

#include <memory>

namespace cstm {
template <class T, class A = std::allocator<T>>
class SomeContainer
{
public:
    SomeContainer() noexcept {}

    ~SomeContainer()
    {
        for (size_t i = 0; i != m_buffer.size(); ++i) {
            m_allocator.destroy(m_buffer[i]);
            m_allocator.deallocate(m_buffer[i], 1);
        }
    }

    void push_back(T& elem) noexcept
    {
        UNUSED(elem);
        auto ptr = m_allocator.allocate(1);
        m_allocator.construct(ptr, elem);

        m_buffer.push_back(ptr);
    }

    T& operator[](size_t idx) { return *m_buffer[idx]; }

private:
    std::vector<T*> m_buffer;
    A m_allocator;
};
} // namespace cstm

#endif // SOME_CONTAINER_HPP
