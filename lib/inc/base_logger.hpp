#ifndef BASE_LOGGER_HPP
#define BASE_LOGGER_HPP

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "aliases.hpp"

namespace logger {
class IBaseLogger
{
public:
    virtual ~IBaseLogger() {}
    void update(const command_block& block)
    {
        std::lock_guard<std::mutex> lg(m_mtx);
        if (!block.empty()) {
            m_buffer.push(block);
            m_condFlag = true;
            m_cv.notify_one();
        }
    }

protected:
    std::atomic<bool> m_condFlag{false};
    std::atomic<bool> m_isWorking{true};
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::queue<command_block> m_buffer;
};
} // namespace logger

#endif // BASE_LOGGER_HPP
