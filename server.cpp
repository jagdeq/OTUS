#include "server.hpp"

Server::Server(boost::asio::io_context& io_context, uint16_t port, size_t bulk_size)
    : m_session_counter{0},
      m_acceptor{io_context, tcp::endpoint(tcp::v4(), port)},
      m_commonContext{-1},
      m_bulkSize{bulk_size}
{
    doAccept();
}

void Server::decreaseSessionCounter()
{
    if (--m_session_counter == 0)
        async::disconnect(m_commonContext);
}

void Server::doAccept()
{
    m_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            if (m_session_counter++ == 0)
                m_commonContext = async::connect(m_bulkSize);

            std::make_shared<Session>(std::move(socket), m_bulkSize, m_commonContext, this)->start();
        }

        doAccept();
    });
}

Session::Session(tcp::socket socket, size_t bulk_size, size_t context, Server* server)
    : m_commonContext{context},
      m_uniqueContext{-1},
      m_bracketsLevel{0},
      m_bulkSize{bulk_size},
      m_socket{std::move(socket)},
      m_server{server}
{}

void Session::doRead()
{
    auto self(shared_from_this());
    m_socket.async_read_some(boost::asio::buffer(m_data), [this, self](boost::system::error_code ec, size_t length) {
        if (!ec)
            parseBuf(length);
        else if (ec == boost::asio::error::eof)
            m_server->decreaseSessionCounter();
    });
}

void Session::parseBuf(size_t length)
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

    doRead();
}
