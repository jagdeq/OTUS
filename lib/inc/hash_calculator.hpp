#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include <boost/algorithm/hex.hpp>

#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>

namespace bayan {
class HashCalculator
{
public:
    using HashFunc = std::string (HashCalculator::*)(const std::vector<char>& data);

    HashCalculator();
    std::string calcHash(const std::vector<char>& data, std::string method);

private:
    std::string md5(const std::vector<char>& data);
    std::string sha1(const std::vector<char>& data);
    /// ... etc
private:
    std::unordered_map<std::string, HashFunc> m_hashMap;
};
} // namespace bayan
