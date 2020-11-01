/*
** EPITECH PROJECT, 2020
** babel's server
** File description: 
** TCP Server header file
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <unordered_set>
#include <optional>
#include <queue>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>
#include "Database.hpp"
#include "BSIPType.hpp"
#include "BSIPInterpreter.hpp"

#define SERVER_PORT 4219

using boost::asio::ip::tcp;
using err_code = boost::system::error_code;
using msg_handler = std::function<void (const bsip::BSIPPackage &package)>;
using err_handler = std::function<void ()>;

namespace BabelServer {
    // Session
    class TCPConnexion : public std::enable_shared_from_this<TCPConnexion> {
    public:
        typedef boost::shared_ptr<TCPConnexion> connector;
        TCPConnexion(tcp::socket&& socket);
        ~TCPConnexion() noexcept = default;
        TCPConnexion(TCPConnexion const &) = delete;
        TCPConnexion(TCPConnexion &&) = delete;
        TCPConnexion &operator=(TCPConnexion const &) = delete;
        TCPConnexion &operator=(TCPConnexion &&) = delete;

        tcp::socket &getSocket();

        const bsip::Sender &getSender() const;

        void start(msg_handler &&on_msg, err_handler &&on_err);
        void post(const bsip::Buffer &msg);
        void async_read();
    private:
        void async_write();
        void on_read(err_code err, std::size_t nbytes);
        void on_write(err_code err, std::size_t nbytes);
    private:
        tcp::socket _socket;
        boost::asio::streambuf _streambuf; // incoming data
        msg_handler _on_message;
        err_handler _on_error;
        std::queue<std::string> _outgoing; // queue of outgoing msgs
        bsip::Sender _sender;
    };

    class TCPServer {
    public:
        TCPServer(boost::asio::io_context &io_context, bsip::BSIPInterpreter &);
        ~TCPServer() noexcept;
        TCPServer(TCPServer const &) = default;
        TCPServer(TCPServer &&) = default;
        TCPServer &operator=(TCPServer const &) = default;
        TCPServer &operator=(TCPServer &&) = default;

        void async_accept_handler();
        //void create_session();
        void handlePacket(const bsip::BSIPPackage &package);
    private:
        tcp::acceptor _acceptor;
        boost::asio::io_context &_io_context;
        std::optional<tcp::socket> _socket;
        std::unordered_set<std::shared_ptr<TCPConnexion>> _clients; // set of connected clients
        bsip::BSIPInterpreter &_interpreter;
    };
}

#endif /* SERVER_HPP_ */
