#include "analyzer.hpp"

namespace bayan {
// Analyzer::Analyzer()
//     : m_hashFunctions{
//           {"md5", &Analyzer::calcMD5},
//           {"sha-1", &Analyzer::calcSHA1},
//           {"sha-256", &Analyzer::calcSHA256},
//       }
// {}

void Analyzer::run(const Options& opt)
{
    // Составление списка файлов
    auto list = getFileList(opt);

    // Анализ дубликатов
    findDuplicate(opt, list);
}

std::vector<fs::path> Analyzer::getFileList(const Options& opt)
{
    std::vector<fs::path> list;

    // auto scanDirs = makeUniqiePaths(opt.m_scanDirs);
    // auto scanDirs = opt.m_scanDirs;

    for (const auto& dir : opt.m_scanDirs)
        for (fs::recursive_directory_iterator it(dir), end; it != end; ++it) {
            if ((std::find(opt.m_ignoreDirs.begin(), opt.m_ignoreDirs.end(), it->path().filename().string()) !=
                 opt.m_ignoreDirs.end()) ||
                it.depth() > static_cast<int>(opt.m_level))
                continue;

            if (it->is_regular_file() && fs::file_size(it->path()) >= opt.m_fileBsize)
                for (const auto& mask : opt.m_masks)
                    if (matchMask(it->path().filename().string(), mask))
                        // list.insert(fs::canonical(it->path()).string());
                        list.emplace_back(it->path());
        }

    return list;
}

void Analyzer::findDuplicate(const Options& opt, const std::vector<fs::path>& list)
{
    std::unordered_map<std::string, std::vector<fs::path>> filesGroups{{"HASH", list}};
    std::unordered_map<std::string, std::vector<fs::path>> tmp;

    std::vector<char> block(opt.m_blockBsize);
    while (true) {
        for (const auto& [hash, group] : filesGroups)
            for (const auto& file : group) {
                std::ifstream f(file, std::ios::binary);
                f.read(block.data(), opt.m_blockBsize);

                if (f.gcount() != opt.m_blockBsize)
                    std::fill(block.begin() + f.gcount(), block.begin() + opt.m_blockBsize - f.gcount(), '\0');

                f.close();

                std::string newHash = hash + calcHash();

                if (tmp.find(newHash) != tmp.end())
                    tmp[newHash].emplace_back(file);
                else
                    tmp.insert({newHash, std::vector<fs::path>{file}});
            }

        /// Если в группе оказался всего один файл - значит это не баян, в игнор его
        for (const auto& [hash, group] : tmp)
            if (group.size() == 1)
                tmp.erase(hash);

        tmp.clear();
        filesGroups = tmp;
    }

    /// Вывод результатов
    for (const auto& [hash, group] : filesGroups) {
        for (const auto& file : group)
            std::cout << fs::canonical(file.string()) << std::endl;
        std::cout << std::endl;
    }
}

bool Analyzer::matchMask(const std::string& filename, const std::string& mask)
{
    std::string filename_l = filename;
    std::string mask_l     = mask;

    std::transform(filename_l.begin(), filename_l.end(), filename_l.begin(), tolower);
    std::transform(mask_l.begin(), mask_l.end(), mask_l.begin(), tolower);

    std::string regex_pattern = std::regex_replace(mask_l, std::regex("\\*"), ".*");

    regex_pattern = std::regex_replace(regex_pattern, std::regex("\\?"), ".");
    std::regex regex(regex_pattern);

    return std::regex_match(filename, regex);
}

std::set<std::string> Analyzer::makeUniqiePaths(const std::vector<std::string>& paths)
{
    std::vector<std::string> fullPaths;
    fullPaths.reserve(paths.size());
    for (auto& path : paths)
        fullPaths.emplace_back(fs::canonical(fs::path(path)).string());

    std::set<std::string> uniquePaths(fullPaths.begin(), fullPaths.end());

    for (auto& path : uniquePaths)
        std::cout << path << std::endl;

    return uniquePaths;
}

// std::string Analyzer::calcMD5(const std::string& data) { return data; }
// std::string Analyzer::calcSHA1(const std::string& data) { return data; }
// std::string Analyzer::calcSHA256(const std::string& data) { return data; }

} // namespace bayan
