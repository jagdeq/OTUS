#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include <fstream>
#include <thread>

#include "base_logger.hpp"

namespace logger {
class FileLogger : public IBaseLogger
{
public:
    FileLogger();

private:
    std::vector<std::thread> m_workers;
};
} // namespace logger

#endif // FILE_LOGGER_HPP
