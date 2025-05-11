#include <iostream>
#include <memory>

#include "async.h"

#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, size_t bulk_size, size_t context)
        : m_commonContext{context},
          m_uniqueContext{-1},
          m_bracketsLevel{0},
          m_bulkSize{bulk_size},
          m_socket{std::move(socket)}
    {}

    // ~Session()
    // {
    //     async::receive(, 0 m_commonContext);
    // }

    void start() { do_read(); }

private:
    void do_read()
    {
        auto self(shared_from_this());
        m_socket.async_read_some(boost::asio::buffer(m_data),
                                 [this, self](boost::system::error_code ec, size_t length) {
                                     if (!ec)
                                         analyze_buf(length);
                                 });
    }

    void analyze_buf(size_t length)
    {
        std::string buf(m_data, length);
        std::stringstream bufstream(buf);

        std::string cmd;
        while (std::getline(bufstream, cmd)) {
            if (cmd == "{") {
                if (m_bracketsLevel == 0)
                    m_uniqueContext = async::connect(m_bulkSize);

                m_bracketsLevel++;
            } else if (cmd == "}" && m_bracketsLevel) {
                m_bracketsLevel--;

                if (m_bracketsLevel == 0)
                    async::disconnect(m_uniqueContext);
            }

            size_t context = (m_bracketsLevel) ? m_uniqueContext : m_commonContext;
            async::receive(cmd.data(), cmd.size(), context);
        }

        do_read();
    }

    size_t m_commonContext;
    ssize_t m_uniqueContext;
    size_t m_bracketsLevel;
    size_t m_bulkSize;
    tcp::socket m_socket;
    char m_data[1024];
};

class Server
{
public:
    Server(boost::asio::io_context& io_context, uint16_t port, size_t bulk_size)
        : m_acceptor{io_context, tcp::endpoint(tcp::v4(), port)},
          m_commonContext{async::connect(bulk_size)},
          m_bulkSize{bulk_size}
    {
        do_accept();
    }

private:
    void do_accept()
    {
        m_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
            if (!ec)
                std::make_shared<Session>(std::move(socket), m_bulkSize, m_commonContext)->start();

            do_accept();
        });
    }

    tcp::acceptor m_acceptor;
    size_t m_commonContext; // общий для статических блоков команд
    size_t m_bulkSize;
};
