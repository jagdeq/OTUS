#include "file_logger.hpp"

namespace {
constexpr size_t g_threadsCount = 2;
}

logger::FileLogger::FileLogger()
{
    m_workers.reserve(g_threadsCount);

    for (size_t i = 0; i != g_threadsCount; ++i) {
        m_workers.push_back(std::thread([this, i]() {
            while (true) {
                {
                    std::unique_lock<std::mutex> ul(m_mtx);
                    m_cv.wait(ul, [this]() { return m_condFlag.load(); });
                    m_condFlag = false;
                }

                while (!m_buffer.empty()) {
                    m_mtx.lock();
                    command_block block = m_buffer.front();
                    m_buffer.pop();
                    m_mtx.unlock();

                    std::ofstream file;
                    std::string filename =
                        "bulk" + std::to_string(block[0].second) + "_id_" + std::to_string(i) + ".log";
                    file.open(filename);

                    if (file.is_open()) {
                        size_t idx{0};
                        for (auto& cmd : block)
                            file << ((idx++ > 0) ? ", " : "bulk: ") << cmd.first;
                        file << '\n';
                        file.close();
                    }

                    if (!m_isWorking && m_buffer.empty())
                        return;
                }
            }
        }));

        m_workers[i].detach();
    }
}
