#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <algorithm>
#include <string>
#include <vector>

#include "aliases.hpp"
#include "base_logger.hpp"

namespace async {
class Analyzer
{
public:
    explicit Analyzer(size_t block_size);

    void parse(const command_pair& pair);
    void attach(logger::IBaseLogger* logger);
    void detach(logger::IBaseLogger* logger);
    void updateAll();

private:
    size_t m_blockSize;
    size_t m_bracketsLevel;
    command_block m_cmdBlock;
    std::vector<logger::IBaseLogger*> m_loggers;
};
} // namespace async

#endif // ANALYZER_HPP
