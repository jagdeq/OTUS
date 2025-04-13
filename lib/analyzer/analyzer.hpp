#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "aliases.hpp"
#include "base_logger.hpp"

class Analyzer
{
public:
    explicit Analyzer(size_t block_size) noexcept;

    void parse(const command_pair& pair) noexcept;
    void attach(logger::IBaseLogger* logger) noexcept;
    void detach(logger::IBaseLogger* logger) noexcept;
    void updateAll() noexcept;

private:
    size_t m_blockSize;
    size_t m_bracketsLevel;
    std::vector<command_pair> m_cmdBlock;
    std::vector<logger::IBaseLogger*> m_loggers;
};

#endif // ANALYZER_HPP
