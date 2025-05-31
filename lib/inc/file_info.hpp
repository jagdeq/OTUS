#pragma once

#include <fstream>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace bayan {
struct FileInfo
{
    fs::path m_path;
    std::ifstream m_stream;

    FileInfo(fs::path path)
        : m_path(path)
    {
        m_stream.open(m_path.string(), std::ios::binary);
        if (!m_stream)
            throw std::runtime_error("Invalid file: " + m_path.string());
    }

    FileInfo(FileInfo&& info) : m_path(info.m_path), m_stream {}

        ~FileInfo()
    {
        if (m_stream.is_open())
            m_stream.close();
    }
};
} // namespace bayan
