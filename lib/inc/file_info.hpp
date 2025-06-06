#pragma once

#include <fstream>
#include <iostream>

// #include <boost/filesystem.hpp>

// namespace fs = boost::filesystem;

namespace bayan {
struct FileInfo
{
    std::string m_path;
    bool m_isEOF;
    size_t m_currentOffset;

    FileInfo(std::string path)
        : m_path(path),
          m_isEOF(false),
          m_currentOffset(0)
    {}

    // ~FileInfo() { std::cout << "logging destr\n"; }
};
} // namespace bayan
