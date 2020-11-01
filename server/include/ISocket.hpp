/*
** EPITECH PROJECT, 2020
** server
** File description:
** ISocket
*/

#ifndef ISOCKET_HPP_
#define ISOCKET_HPP_

struct ISocket {
    virtual ISocket() = default;

    virtual void read() = 0;
    virtual void write() = 0;
    virtual void connect() = 0;
    virtual void shutdown() = 0;
    virtual void close() = 0;
};

#endif /* ISOCKET_HPP_ */

