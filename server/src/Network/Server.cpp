/*
** EPITECH PROJECT, 2020
** server
** File description:
** Server
*/

#include "Server.hpp"

Network::TcpSocket::TcpSocket(tcp::socket &&Socket)
    : socket_(std::move)
{
}
