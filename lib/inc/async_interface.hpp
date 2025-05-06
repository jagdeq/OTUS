#ifndef ASYNC_INTERFACE_HPP
#define ASYNC_INTERFACE_HPP

#include <chrono>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "analyzer.hpp"
#include "console_logger.hpp"
#include "file_logger.hpp"

namespace async {

class IAsync
{
public:
    static IAsync& getInstance()
    {
        static IAsync instance;
        return instance;
    }

    size_t connect(size_t block_size);
    void disconnect(size_t context);
    void receive(const std::vector<std::string>& buf, size_t context);

private:
    IAsync();
    ~IAsync();

    IAsync(const IAsync& async)            = delete;
    IAsync& operator=(const IAsync& async) = delete;

    uint64_t getTimePoint() { return std::chrono::system_clock::now().time_since_epoch().count(); }

private:
    std::mutex m_mtx;
    size_t currentID;
    logger::ConsoleLogger* m_pConsoleLogger;
    logger::FileLogger* m_pFileLogger;
    std::unordered_map<size_t, std::unique_ptr<async::Analyzer>> m_contextMap;
};
} // namespace async

#endif // ASYNC_INTERFACE_HPP
