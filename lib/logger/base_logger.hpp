#ifndef BASE_LOGGER_HPP
#define BASE_LOGGER_HPP

#include <vector>

#include "aliases.hpp"

namespace logger {
class IBaseLogger
{
public:
    virtual ~IBaseLogger() noexcept {}
    virtual void update(const std::vector<command_pair>& block) noexcept = 0;
};
} // namespace logger

#endif // BASE_LOGGER_HPP
