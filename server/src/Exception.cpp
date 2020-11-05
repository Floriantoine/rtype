/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Exception
*/

#include "Exception.hpp"

namespace rtype::server {
    Exception::Exception(const std::string &msg)
        : rtype::Exception("Server exception: " + msg)
    {
    }

    Exception::Exception(std::string &&msg)
        : rtype::Exception("Server exception: " + std::move(msg))
    {
    }
}