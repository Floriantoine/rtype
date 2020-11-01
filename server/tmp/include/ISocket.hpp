/*
** EPITECH PROJECT, 2020
** server
** File description:
** ISocket
*/

#ifndef ISOCKET_HPP_
#define ISOCKET_HPP_

struct ISocket
{
    virtual ~ISocket() = default;
    
    virtual void start() = 0;
    //virtual void end() = 0;
    //virtual void listen() = 0;
    //virtual void connect() = 0;

    //virtual void broadcast(const std::string_view &data) = 0;
    //virtual void read() = 0;
    //virtual void write(const std::string_view &data) = 0;
    //virtual void sendToClient(const std::string_view &ip_adress, const std::string_view &data) = 0;
    //virtual bool isOpen() const = 0;
};

#endif /* ISOCKET_HPP_ */

