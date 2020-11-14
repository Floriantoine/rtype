/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Exception
*/

#include "Exception.hpp"

namespace rtype::server {
    Exception::Exception(const std::string &msg)
        : rtype::Exception("GameServer exception: " + msg)
    {
    }

    Exception::Exception(std::string &&msg)
        : rtype::Exception("GameServer exception: " + std::move(msg))
    {
    }

    Network::IOException::IOException(const std::string &msg)
        : rtype::Exception("Network I/O exception: " + msg)
    {
    }

    Network::IOException::IOException(std::string &&msg)
        : rtype::Exception("Network I/O exception: " + std::move(msg))
    {
    }
    Network::IOException::IOException(const std::string &msg, const std::string &part)
        : rtype::Exception("Network I/O exception: " + msg, part)
    {
    }

    Network::IOException::IOException(std::string &&msg, std::string &&part)
        : rtype::Exception("Network I/O exception: " + std::move(msg), std::move(part))
    {
    }
}
