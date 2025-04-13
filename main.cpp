#include <chrono>
#include <iostream>
#include <string>
#include <utility>

#include "analyzer.hpp"
#include "console_logger.hpp"
#include "file_logger.hpp"

/// @brief Логика приёма команд реализована в main-е, тк посчитал нецелесообразным создавать целый класс
/// для одного метода
int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Incorrect input. Set command line block.\n";
        std::cout << "Example: ./bulk 3\n";
        return 0;
    }

    logger::FileLogger flogger;
    logger::ConsoleLogger clogger;
    Analyzer analyzer(std::stol(argv[1]));

    analyzer.attach(&flogger);
    analyzer.attach(&clogger);

    for (std::string line; std::getline(std::cin, line);)
        analyzer.parse(std::make_pair(line, std::chrono::system_clock::now().time_since_epoch().count()));

    return 0;
}
