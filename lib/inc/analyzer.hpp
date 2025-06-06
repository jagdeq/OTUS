#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <unordered_set>

#include <boost/filesystem.hpp>

using HashFunc = std::function<std::string(const std::vector<char>&)>;

#include "consts.hpp"
#include "file_info.hpp"
#include "hash_calculator.hpp"
#include "options.hpp"

#define UNUSED(x) (void)(x)

namespace fs = boost::filesystem;

namespace bayan {
class Analyzer
{
public:
    void run(const Options& opt);

private:
    std::unordered_set<std::string> getFileList(const Options& opt);
    void findDuplicate(const Options& opt, const std::unordered_set<std::string>& list);
    bool matchMask(const std::string& filename, const std::string& mask);

private:
    HashCalculator m_calculator;
};

} // namespace bayan
