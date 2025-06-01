#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "async.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cout << "Incorrect input. Set command line block.\n";
        std::cout << "Example: ./async_cli 3\n";
        return 0;
    }

    auto context = async::connect(atoi(argv[1]));
    for (std::string cmd; std::getline(std::cin, cmd);)
        async::receive(cmd.data(), cmd.size(), context);
    async::disconnect(context);

    while (true) {}

    return 0;
}
