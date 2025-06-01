#ifndef CONSOLE_LOGGER_HPP
#define CONSOLE_LOGGER_HPP

#include <iostream>

#include "base_logger.hpp"

namespace logger {
class ConsoleLogger : public IBaseLogger
{
public:
    ConsoleLogger();
};
} // namespace logger

#endif // CONSOLE_LOGGER_HPP
