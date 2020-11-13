/*
** EPITECH PROJECT, 2020
** server
** File description:
** IServer
*/

#ifndef ISERVER_HPP_
#define ISERVER_HPP_

struct IServer {
    virtual ~IServer() = 0;
    virtual void start();
    virtual void end();
    virtual void write();
    virtual void read();
};

#endif /* ISERVER_HPP_ */
