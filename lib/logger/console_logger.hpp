#ifndef CONSOLE_LOGGER_HPP
#define CONSOLE_LOGGER_HPP

#include <iostream>

#include "base_logger.hpp"

namespace logger {
class ConsoleLogger : public IBaseLogger
{
public:
    void update(const std::vector<command_pair>& block) noexcept override;
};
} // namespace logger

#endif // CONSOLE_LOGGER_HPP
