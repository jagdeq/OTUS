#include "hash_calculator.hpp"

namespace bayan {
HashCalculator::HashCalculator()
    : m_hashMap{{"md5", &HashCalculator::md5}, {"sha-1", &HashCalculator::sha1}}
{}

std::string HashCalculator::calcHash(const std::vector<char>& data, std::string method)
{
    if (m_hashMap.find(method) == m_hashMap.end())
        throw std::invalid_argument("Unknown hash method");

    return (this->*m_hashMap[method])(data);
}

std::string HashCalculator::md5(const std::vector<char>& data)
{
    using boost::uuids::detail::md5;
    md5 hash;

    hash.process_bytes(data.data(), data.size());
    md5::digest_type digest;
    hash.get_digest(digest);

    const auto intDigest = reinterpret_cast<const int*>(&digest);
    std::string result;
    boost::algorithm::hex(intDigest, intDigest + (sizeof(md5::digest_type) / sizeof(int)), std::back_inserter(result));

    return result;
}

/// Да, сейчас она почти полностью дублирует функцию для md5, но не хочу привязываться к реализации
std::string HashCalculator::sha1(const std::vector<char>& data)
{
    using boost::uuids::detail::sha1;
    sha1 hash;

    hash.process_bytes(data.data(), data.size());
    sha1::digest_type digest;
    hash.get_digest(digest);

    const auto intDigest = reinterpret_cast<const int*>(&digest);
    std::string result;
    boost::algorithm::hex(intDigest, intDigest + (sizeof(sha1::digest_type) / sizeof(int)), std::back_inserter(result));

    return result;
}

} // namespace bayan
