#include "ip_filter.hpp"

uint32_t ip::convertAddrToBytes(const std::string& ipv4)
{
    if (std::count(ipv4.begin(), ipv4.end(), '.') != sizeof(uint32_t) - 1)
        throw std::invalid_argument("Invalid dots count in address");

    uint32_t addr(0);
    std::string addrByte;

    int convertedByte;
    size_t start = 0;
    size_t stop  = ipv4.find_first_of('.');
    for (size_t i = 0; i != sizeof(uint32_t); ++i) {
        if (stop == ipv4.npos)
            stop = ipv4.size();

        addrByte = ipv4.substr(start, stop - start);

        if (addrByte.empty())
            throw std::invalid_argument("Empty byte");

        convertedByte = std::stoi(addrByte);
        if (convertedByte < 0)
            throw std::invalid_argument("Bytes must be positive");
        else if (convertedByte > 255)
            throw std::invalid_argument("Byte overflow");

        addr |= static_cast<uint8_t>(convertedByte) << (sizeof(uint32_t) - i - 1) * 8;

        start = stop + 1;
        stop  = ipv4.find_first_of('.', start);
    }

    return addr;
}

std::string ip::convertBytesToAddr(const uint32_t& addr_bytes) noexcept
{
    std::string ipv4 = std::to_string(addr_bytes >> 24 & 0xFF) + '.' + std::to_string(addr_bytes >> 16 & 0xFF) + '.' +
                       std::to_string(addr_bytes >> 8 & 0xFF) + '.' + std::to_string(addr_bytes & 0xFF);
    return ipv4;
}

std::vector<std::string> ip::reverseSort(const std::vector<std::string>& ip_pool) noexcept
{
    std::vector<uint32_t> ipBytes;
    std::vector<std::string> sortedPool;
    ipBytes.reserve(ip_pool.size());
    sortedPool.reserve(ip_pool.size());

    for (size_t i = 0; i != ip_pool.size(); ++i)
        ipBytes.emplace_back(convertAddrToBytes(ip_pool[i].data()));

    std::sort(ipBytes.begin(), ipBytes.end(), std::greater<uint32_t>());

    for (size_t i = 0; i != ipBytes.size(); ++i)
        sortedPool.emplace_back(convertBytesToAddr(ipBytes[i]));

    return sortedPool;
}

std::vector<std::string> ip::filterByFirstByte(const std::vector<std::string>& ip_pool, uint8_t fbyte) noexcept
{
    std::vector<std::string> filteredPool;

    for (size_t i = 0; i != ip_pool.size(); ++i)
        if ((convertAddrToBytes(ip_pool[i]) >> 24 & 0xFF) == fbyte)
            filteredPool.push_back(ip_pool[i]);

    return filteredPool;
}

std::vector<std::string> ip::filterByFirstTwoBytes(const std::vector<std::string>& ip_pool, uint8_t fbyte,
                                                   uint8_t sbyte) noexcept
{
    uint32_t addr(0);
    std::vector<std::string> filteredPool;

    for (size_t i = 0; i != ip_pool.size(); ++i) {
        addr = convertAddrToBytes(ip_pool[i]);
        if (((addr >> 24 & 0xFF) == fbyte) && ((addr >> 16 & 0xFF) == sbyte))
            filteredPool.push_back(ip_pool[i]);
    }

    return filteredPool;
}

std::vector<std::string> ip::filterByAnyByte(const std::vector<std::string>& ip_pool, uint8_t byte) noexcept
{
    uint32_t addr(0);
    std::vector<std::string> filteredPool;

    for (size_t i = 0; i != ip_pool.size(); ++i) {
        addr = convertAddrToBytes(ip_pool[i]);
        if (((addr >> 24 & 0xFF) == byte) || ((addr >> 16 & 0xFF) == byte) || ((addr >> 8 & 0xFF) == byte) ||
            ((addr & 0xFF) == byte))
            filteredPool.push_back(ip_pool[i]);
    }

    return filteredPool;
}
