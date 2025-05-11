#include <iostream>

#include "server.hpp"

#include <boost/program_options.hpp>

namespace ba = boost::asio;
namespace po = boost::program_options;

int main(int argc, char** argv)
{
    uint16_t port    = 0;
    size_t bulk_size = 0;

    po::options_description desc("Allowed options");
    desc.add_options()
        // help
        ("help,h", "produce help message")
        // listenng port
        ("port,p", po::value<uint16_t>()->required(), "listening port")
        // bulk size
        ("bulk_size,s", po::value<size_t>()->required(), "command block size");

    po::positional_options_description pod;
    pod.add("port", 1);
    pod.add("bulk_size", 1);

    po::variables_map vm;

    try {
        po::store(po::command_line_parser(argc, argv).options(desc).positional(pod).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc;
            return 0;
        }

        if (vm.count("port"))
            port = vm["port"].as<uint16_t>();

        if (vm.count("bulk_size"))
            bulk_size = vm["bulk_size"].as<size_t>();

    } catch (const po::error& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        std::cerr << desc << "\n";
        return 1;
    }

    std::cout << "Server starting...\n";
    std::cout << "\tlistening port: " << port << std::endl;
    std::cout << "\tbulk_size: " << bulk_size << std::endl;

    ba::io_context io_context;
    Server server(io_context, port, bulk_size);
    io_context.run();

    return 0;
}
