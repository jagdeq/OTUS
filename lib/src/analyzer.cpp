#include "analyzer.hpp"

async::Analyzer::Analyzer(size_t block_size)
    : m_blockSize{block_size},
      m_bracketsLevel{0}
{}

void async::Analyzer::parse(const command_pair& pair)
{
    const std::string& cmd = pair.first;

    if (cmd == "{") {
        // Если уже был набранный блок
        if (!m_cmdBlock.empty() && m_bracketsLevel == 0)
            updateAll();
        m_bracketsLevel++;
        return;
    } else if (cmd == "}")
        m_bracketsLevel--;
    else if (!cmd.empty())
        m_cmdBlock.push_back(pair);

    if (m_bracketsLevel == 0 && !m_cmdBlock.empty() && (m_cmdBlock.size() == m_blockSize || cmd == "}" || cmd.empty()))
        updateAll();
}

void async::Analyzer::attach(logger::IBaseLogger* logger) { m_loggers.push_back(logger); }

void async::Analyzer::detach(logger::IBaseLogger* logger)
{
    auto it = std::find(m_loggers.begin(), m_loggers.end(), logger);
    if (it != m_loggers.end())
        m_loggers.erase(it);
}

void async::Analyzer::updateAll()
{
    for (auto logger : m_loggers)
        logger->update(m_cmdBlock);

    m_cmdBlock.clear();
}
