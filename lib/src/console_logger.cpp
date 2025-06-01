#include "console_logger.hpp"

logger::ConsoleLogger::ConsoleLogger()
{
    std::thread th([this]() {
        while (true) {
            {
                std::unique_lock<std::mutex> ul(m_mtx);
                m_cv.wait(ul, [this]() { return m_condFlag.load(); });
                m_condFlag = false;
            }

            while (!m_buffer.empty()) {
                // m_mtx.lock();
                command_block block = m_buffer.front();
                m_buffer.pop();
                // m_mtx.unlock();

                size_t idx{0};
                for (auto& cmd : block)
                    std::cout << ((idx++ > 0) ? ", " : "bulk: ") << cmd.first;
                std::cout << std::endl;

                if (!m_isWorking && m_buffer.empty())
                    return;
            }
        }
    });

    th.detach();
}
