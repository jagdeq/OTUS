#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace bayan {
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (const auto& el : vec)
        os << el << " ";

    return os;
}

struct Options
{
    std::vector<std::string> m_scanDirs;
    std::vector<std::string> m_ignoreDirs;
    std::vector<std::string> m_masks{"*"};
    size_t m_level      = 0;
    size_t m_fileBsize  = 1;
    size_t m_blockBsize = 5;
    std::string m_hash{"md5"};

    friend std::ostream& operator<<(std::ostream& os, const Options& opt)
    {
        os << "-----------------------------------------------------------------------\n"
           << "scanning dirs:      " << opt.m_scanDirs << "\n"
           << "ignored dirs:       " << opt.m_ignoreDirs << "\n"
           << "filename masks:     " << opt.m_masks << "\n"
           << "scanning level      " << opt.m_level << "\n"
           << "minimal file size:  " << opt.m_fileBsize << "\n"
           << "reading block size: " << opt.m_blockBsize << "\n"
           << "hash function:      " << opt.m_hash << "\n"
           << "-----------------------------------------------------------------------\n";

        return os;
    }
};
}; // namespace bayan
