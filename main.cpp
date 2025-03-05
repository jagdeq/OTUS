// #include <functional>
#include <iostream>
#include <list>
#include <map>
#include <vector>
// #include <memory>

#include "logging_allocator.hpp"
#include "reserve_allocator.hpp"
#include "some_container.hpp"

constexpr size_t g_nElements = 10;

int factorial(int n) { return (n == 0) ? 1 : n * factorial(n - 1); }

int main()
{
    /// Allocator
    std::map<int, int> mapStandart;
    for (int i = 0; i != g_nElements; ++i)
        mapStandart.insert({i, factorial(i)});

    std::map<int, int, std::less<int>, cstm::ReserveAllocator<std::pair<const int, int>, g_nElements>> mapNewAllocator;
    for (int i = 0; i != g_nElements; ++i)
        mapNewAllocator.insert({i, factorial(i)});

    for (auto p : mapNewAllocator)
        std::cout << p.first << " " << p.second << std::endl;

    /// Container
    cstm::SomeContainer<int> container;
    for (int i = 0; i != g_nElements; ++i)
        container.push_back(i);

    cstm::SomeContainer<int, cstm::ReserveAllocator<int>> contWithCAlloc;
    for (int i = 0; i != g_nElements; ++i)
        contWithCAlloc.push_back(i);

    for (size_t i = 0; i != g_nElements; ++i)
        std::cout << contWithCAlloc[i] << std::endl;

    return 0;
}
