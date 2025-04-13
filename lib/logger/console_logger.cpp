#include "console_logger.hpp"

void logger::ConsoleLogger::update(const std::vector<command_pair>& block) noexcept
{
    size_t idx{0};
    for (auto& cmd : block)
        std::cout << ((idx++ > 0) ? ", " : "bulk: ") << cmd.first;

    std::cout << std::endl;
}
