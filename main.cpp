#include <iostream>

#include "server.hpp"

namespace ba = boost::asio;

int main(int argc, char** argv)
{
    uint16_t port{0};

    if (argc == 2)
        port = atoi(argv[1]);
    else {
        std::cout << "Invalid input. Use port number as a command line argument [1024 : 65535]\n";
        return 0;
    }

    std::cout << "Server starting...\n";
    std::cout << "\tlistening port: " << port << std::endl;

    ba::io_context io_context;
    proto::Server server(io_context, port);
    io_context.run();

    return 0;
}
