#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

#include "database.hpp"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace proto {
class Session : public std::enable_shared_from_this<Session>
{
public:
    using cmd = void (Session::*)(const std::vector<std::string>& args);

    Session(tcp::socket socket, db::Database& db);

    void start() { doRead(); }

private:
    void doRead();
    void parseBuf(size_t length);

    void callInsert(const std::vector<std::string>& args);
    void callTruncate(const std::vector<std::string>& args);
    void callIntersection(const std::vector<std::string>& args);
    void callSymDifference(const std::vector<std::string>& args);

private:
    tcp::socket m_socket;
    db::Database& m_rDB;
    std::unordered_map<std::string, cmd> m_cmdFuncs;
    char m_data[1024];
};

class Server
{
public:
    Server(boost::asio::io_context& io_context, uint16_t port);
    ~Server();

private:
    void doAccept();

private:
    db::Database* m_pDB;
    tcp::acceptor m_acceptor;
};
} // namespace proto
