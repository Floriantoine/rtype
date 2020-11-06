/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyIDGenerator
*/

#include "LobbyIDGenerator.hpp"

namespace rtype::server {
    LobbyIDGenerator::LobbyIDGenerator()
        : gen_ { std::random_device()() }
        , rand_ { 0, 25 }
    {
    }

    std::string LobbyIDGenerator::operator()()
    {
        std::string ret;

        ret += static_cast<char>('A' + this->rand_(this->gen_));
        ret += static_cast<char>('A' + this->rand_(this->gen_));
        ret += static_cast<char>('A' + this->rand_(this->gen_));
        ret += static_cast<char>('A' + this->rand_(this->gen_));
        ret += static_cast<char>('A' + this->rand_(this->gen_));
        ret += static_cast<char>('A' + this->rand_(this->gen_));
        return (ret);
    }
}