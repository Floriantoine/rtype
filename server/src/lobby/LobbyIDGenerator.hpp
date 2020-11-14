/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyIDGenerator
*/

#pragma once

#include <random>
#include <string>

namespace rtype::server {
    class LobbyIDGenerator {
      private:
        std::mt19937 gen_;
        std::uniform_int_distribution<int> rand_;

      public:
        LobbyIDGenerator();
        std::string operator()();
    };
}
