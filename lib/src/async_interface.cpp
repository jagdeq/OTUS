#include "async_interface.hpp"

async::IAsync::IAsync()
    : currentID{0},
      m_pConsoleLogger{new logger::ConsoleLogger},
      m_pFileLogger{new logger::FileLogger}
{}

async::IAsync::~IAsync()
{
    delete m_pFileLogger;
    delete m_pConsoleLogger;
}

size_t async::IAsync::connect(size_t block_size)
{
    std::lock_guard<std::mutex> lg(m_mtx);
    size_t lastID = currentID++;

    m_contextMap.insert({lastID, std::make_unique<Analyzer>(block_size)});
    (*m_contextMap[lastID]).attach(m_pConsoleLogger);
    (*m_contextMap[lastID]).attach(m_pFileLogger);

    return lastID++;
}

void async::IAsync::receive(const std::vector<std::string>& buf, size_t context)
{
    std::lock_guard<std::mutex> lg(m_mtx);

    if (m_contextMap.find(context) == m_contextMap.end())
        throw std::invalid_argument("Invalid context");

    for (const std::string& cmd : buf)
        (*m_contextMap[context]).parse(std::make_pair(cmd, getTimePoint()));
}

void async::IAsync::disconnect(size_t context)
{
    std::lock_guard<std::mutex> lg(m_mtx);

    if (m_contextMap.find(context) == m_contextMap.end())
        throw std::invalid_argument("Invalid context");

    (*m_contextMap[context]).parse(std::make_pair("", getTimePoint()));
    m_contextMap.erase(context);
}
