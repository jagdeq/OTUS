#ifndef IP_FILTER_HPP
#define IP_FILTER_HPP

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include <arpa/inet.h>

namespace ip {
uint32_t convertAddrToBytes(const std::string& ipv4);
std::string convertBytesToAddr(const uint32_t& addr_bytes) noexcept;
std::vector<std::string> reverseSort(const std::vector<std::string>& ip_pool) noexcept;
std::vector<std::string> filterByFirstByte(const std::vector<std::string>& ip_pool, uint8_t fbyte) noexcept;
std::vector<std::string> filterByFirstTwoBytes(const std::vector<std::string>& ip_pool, uint8_t fbyte,
                                               uint8_t sbyte) noexcept;
std::vector<std::string> filterByAnyByte(const std::vector<std::string>& ip_pool, uint8_t byte) noexcept;
} // namespace ip

#endif // IP_FILTER_HPP
