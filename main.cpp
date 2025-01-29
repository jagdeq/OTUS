#include <iostream>

#include "ip_filter.hpp"

int main()
{
    std::vector<std::string> ipPool;

    // parse
    for (std::string line; std::getline(std::cin, line);)
        ipPool.push_back(line.substr(0, line.find_first_of('\t')));

    // check
    std::vector<std::string> sortedPool = ip::reverseSort(ipPool);
    for (auto addr : sortedPool)
        std::cout << addr << std::endl;

    std::vector<std::string> pool_46 = ip::filterByFirstByte(sortedPool, 1);
    for (auto addr : pool_46)
        std::cout << addr << std::endl;

    std::vector<std::string> pool_46_70 = ip::filterByFirstTwoBytes(sortedPool, 46, 70);
    for (auto addr : pool_46_70)
        std::cout << addr << std::endl;

    std::vector<std::string> pool_any_46 = ip::filterByAnyByte(sortedPool, 46);
    for (auto addr : pool_any_46)
        std::cout << addr << std::endl;

    return 0;
}
