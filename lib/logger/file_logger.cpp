#include "file_logger.hpp"

#include <iostream>

void logger::FileLogger::update(const std::vector<command_pair>& block) noexcept
{
    // std::cout << block.size() << std::endl;
    std::ofstream file;
    std::string filename = "bulk" + std::to_string(block[0].second) + ".log";
    file.open(filename);
    file << "bulk: ";

    if (file.is_open()) {
        size_t idx{0};
        for (auto& cmd : block)
            file << ((idx++ > 0) ? ", " : "") << cmd.first;
        file << '\n';
    }

    file.close();
}
