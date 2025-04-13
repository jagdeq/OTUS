#include "analyzer.hpp"

Analyzer::Analyzer(size_t block_size) noexcept
    : m_blockSize{block_size},
      m_bracketsLevel{0}
{}

void Analyzer::parse(const command_pair& pair) noexcept
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

    if (m_bracketsLevel == 0 && (m_cmdBlock.size() == m_blockSize || cmd == "}" || cmd.empty()))
        updateAll();
}

void Analyzer::attach(logger::IBaseLogger* logger) noexcept { m_loggers.push_back(logger); }

void Analyzer::detach(logger::IBaseLogger* logger) noexcept
{
    auto it = std::find(m_loggers.begin(), m_loggers.end(), logger);
    if (it != m_loggers.end())
        m_loggers.erase(it);
}

void Analyzer::updateAll() noexcept
{
    /// В случае многопотоковой обработки просто передавать по значению
    for (auto logger : m_loggers)
        logger->update(m_cmdBlock);

    m_cmdBlock.clear();
}
