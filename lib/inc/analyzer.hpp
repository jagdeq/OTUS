#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <unordered_set>

#include <boost/filesystem.hpp>

#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>

// #define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

// #include <cryptopp/filters.h>
// #include <cryptopp/hex.h>
// #include <cryptopp/sha.h>

// #include <cryptopp/md5.h>
#include "consts.hpp"
#include "file_info.hpp"
#include "options.hpp"

#define UNUSED(x) (void)(x)

namespace fs = boost::filesystem;

namespace bayan {
class Analyzer
{
public:
    // Analyzer();
    void run(const Options& opt);

private:
    std::vector<fs::path> getFileList(const Options& opt);
    void findDuplicate(const Options& opt, const std::vector<fs::path>& list);
    bool matchMask(const std::string& filename, const std::string& mask);
    std::set<std::string> makeUniqiePaths(const std::vector<std::string>& paths);

    /// Расчёт хэшей
    template <typename T>
    std::string calcHash(const std::string& data, T hash)
    {
        std::string digest;
        CryptoPP::StringSource s(
            data, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
        return digest;
    }

    // std::string calcMD5(const std::string& data);
    // std::string calcSHA1(const std::string& data);
    // std::string calcSHA256(const std::string& data);

private:
    // using p = std::string (Analyzer::*)(const std::string&);
    // std::unordered_map<std::string, p> m_hashFunctions;
};

} // namespace bayan
