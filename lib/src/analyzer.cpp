#include "analyzer.hpp"

namespace bayan {
void Analyzer::run(const Options& opt)
{
    // Составление списка файлов
    auto list = getFileList(opt);

    // Анализ дубликатов
    findDuplicate(opt, list);
}

std::unordered_set<std::string> Analyzer::getFileList(const Options& opt)
{
    std::unordered_set<std::string> list;

    auto scanDirs = makeUniqiePaths(opt.m_scanDirs);

    for (const auto& dir : scanDirs)
        for (fs::recursive_directory_iterator it(dir), end; it != end; ++it) {
            if (it->is_regular_file())
                for (const auto& mask : opt.m_masks)
                    if (matchMask(it->path().filename().string(), mask))
                        list.insert(fs::canonical(it->path()).string());

            if (std::find(opt.m_ignoreDirs.begin(), opt.m_ignoreDirs.end(), it->path().filename().string()) !=
                    opt.m_ignoreDirs.end() ||
                it.depth() > static_cast<int>(opt.m_level))
                it.disable_recursion_pending();
        }

    return list;
}

void Analyzer::findDuplicate(const Options& opt, const std::unordered_set<std::string>& list)
{
    // TODO
    UNUSED(opt);

    for (const auto& file : list)
        std::cout << file << std::endl;
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

} // namespace bayan
