#include "analyzer.hpp"

namespace bayan {
void Analyzer::run(const Options& opt)
{
    // Перечень файлов, содержащихся в директориях
    auto list = getFileList(opt);

    // Анализ дубликатов
    findDuplicate(opt, list);
}

std::unordered_set<std::string> Analyzer::getFileList(const Options& opt)
{
    std::unordered_set<std::string> list;

    for (const auto& dir : opt.m_scanDirs)
        for (fs::recursive_directory_iterator it(dir), end; it != end; ++it) {
            if (it->is_directory())
                for (const auto& dir : opt.m_ignoreDirs)
                    if (it->path().string().find(dir) != it->path().string().npos)
                        it.disable_recursion_pending();

            if (it.depth() > static_cast<int>(opt.m_level))
                continue;

            if (it->is_regular_file() && fs::file_size(it->path()) >= opt.m_fileBsize)
                for (const auto& mask : opt.m_masks)
                    if (matchMask(it->path().filename().string(), mask))
                        list.insert(fs::canonical(it->path()).string());
        }

    return list;
}

void Analyzer::findDuplicate(const Options& opt, const std::unordered_set<std::string>& list)
{
    std::vector<FileInfo> info;
    info.reserve(list.size());
    for (auto& file : list)
        info.emplace_back(FileInfo(file));

    std::unordered_map<std::string, std::vector<FileInfo>> fileGroups{{"0x", info}};
    std::unordered_map<std::string, std::vector<FileInfo>> tmp;
    std::unordered_map<std::string, std::vector<FileInfo>> doneGroups;

    std::vector<char> block(opt.m_blockBsize);
    size_t filesHandled{0};
    while (filesHandled != list.size()) {
        for (auto& [hash, group] : fileGroups) {
            for (auto& file : group) {
                std::ifstream f(file.m_path, std::ios::binary);
                f.seekg(file.m_currentOffset);
                f.read(block.data(), opt.m_blockBsize);

                if (static_cast<size_t>(f.gcount()) != opt.m_blockBsize) {
                    std::fill(block.begin() + f.gcount(), block.begin() + opt.m_blockBsize, '\0');
                    file.m_isEOF = true;
                }

                f.close();
                std::string newHash = hash + m_calculator.calcHash(block, opt.m_hash);
                file.m_currentOffset += opt.m_blockBsize;

                if (tmp.find(newHash) != tmp.end())
                    tmp[newHash].emplace_back(file);
                else
                    tmp.insert({newHash, std::vector<FileInfo>{FileInfo(file)}});
            }
        }

        fileGroups.clear();
        for (const auto& [hash, group] : tmp) {
            size_t eofCount{0};
            for (const auto& file : group)
                if (file.m_isEOF)
                    eofCount++;

            /// Если в группе оказался всего один файл - значит это не баян, в игнор его
            /// Если группа уже завершена, она исключается из обработки
            if (group.size() == eofCount || group.size() == 1) {
                if (group.size() != 1)
                    doneGroups.insert({hash, group});

                filesHandled += group.size();
            } else
                fileGroups.insert({hash, group});
        }

        tmp.clear();
    }

    /// Вывод результатов
    bool isFirstGroup = true;

    for (const auto& [hash, group] : doneGroups) {
        if (isFirstGroup)
            isFirstGroup = false;
        else
            std::cout << std::endl;

        for (const auto& file : group)
            std::cout << file.m_path << std::endl;
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

} // namespace bayan
