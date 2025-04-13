#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include <fstream>

#include "base_logger.hpp"

namespace logger {
class FileLogger : public IBaseLogger
{
public:
    void update(const std::vector<command_pair>& block) noexcept override;
};
} // namespace logger

#endif // FILE_LOGGER_HPP
