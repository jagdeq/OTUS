#include <algorithm>
#include <iostream>
#include <regex>
#include <set>
#include <unordered_set>

#include <boost/filesystem.hpp>
// #include <boost/regex.hpp>

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
    std::set<std::string> makeUniqiePaths(const std::vector<std::string>& paths);
};

} // namespace bayan
