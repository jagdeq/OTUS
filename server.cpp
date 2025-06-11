#include "server.hpp"

namespace proto {
Server::Server(boost::asio::io_context& io_context, uint16_t port)
    : m_pDB{new db::Database},
      m_acceptor{io_context, tcp::endpoint(tcp::v4(), port)}
{
    doAccept();
}

Server::~Server() { delete m_pDB; }

void Server::doAccept()
{
    m_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec)
            std::make_shared<Session>(std::move(socket), *m_pDB)->start();

        doAccept();
    });
}

Session::Session(tcp::socket socket, db::Database& db)
    : m_socket{std::move(socket)},
      m_rDB{db},
      m_cmdFuncs{{"INSERT", &Session::callInsert},
                 {"TRUNCATE", &Session::callTruncate},
                 {"INTERSECTION", &Session::callIntersection},
                 {"SYMMETRIC_DIFFERENCE", &Session::callSymDifference}}
{}

void Session::doRead()
{
    auto self(shared_from_this());
    m_socket.async_read_some(boost::asio::buffer(m_data), [this, self](boost::system::error_code ec, size_t length) {
        if (!ec)
            parseBuf(length);
    });
}

void Session::parseBuf(size_t length)
{
    if (length != 0) {
        std::string line(m_data, length);
        std::vector<std::string> args;

        std::string tmp;
        std::stringstream ss(line);
        while (ss >> tmp)
            args.push_back(tmp);

        if (m_cmdFuncs.find(args[0]) != m_cmdFuncs.end())
            (this->*m_cmdFuncs[args[0]])(std::vector<std::string>(args.begin() + 1, args.end()));
    }

    doRead();
}

void Session::callInsert(const std::vector<std::string>& args)
{
    if (args.size() != 3)
        return;

    m_rDB.insert(args[0], atoi(args[1].data()), args[2]);
}

void Session::callTruncate(const std::vector<std::string>& args)
{
    if (args.size() != 1)
        return;

    m_rDB.truncate(args[0]);
}

void Session::callIntersection(const std::vector<std::string>& args)
{
    using namespace db;

    if (!args.empty())
        return;

    auto c = m_rDB.intersection("A", "B");
    std::cout << "id | A | B\n";
    std::cout << "-------------------------------\n";
    std::cout << c << std::endl;
}

void Session::callSymDifference(const std::vector<std::string>& args)
{
    using namespace db;

    if (!args.empty())
        return;

    auto c = m_rDB.symmetricDifference("A", "B");
    std::cout << "id | A | B\n";
    std::cout << "-------------------------------\n";
    std::cout << c << std::endl;
}

} // namespace proto
