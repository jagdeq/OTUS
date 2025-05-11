#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <memory>

#include "async.h"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, size_t bulk_size, size_t context, Server* server);

    void start() { doRead(); }

private:
    void doRead();
    void parseBuf(size_t length);

private:
    size_t m_commonContext;
    ssize_t m_uniqueContext;
    size_t m_bracketsLevel;
    size_t m_bulkSize;
    tcp::socket m_socket;
    Server* m_server;
    char m_data[1024];
};

class Server
{
public:
    Server(boost::asio::io_context& io_context, uint16_t port, size_t bulk_size);

    void decreaseSessionCounter();

private:
    void doAccept();

private:
    size_t m_session_counter;
    tcp::acceptor m_acceptor;
    ssize_t m_commonContext; // общий для статических блоков команд
    size_t m_bulkSize;
};

#endif // SERVER_HPP
