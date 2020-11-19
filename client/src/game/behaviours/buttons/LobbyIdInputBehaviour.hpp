/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** LobbyIdInputBehaviour
*/

#pragma once

#include "game/behaviours/TextInputBehaviour.hpp"

namespace rtype::client {

    class LobbyIdInputBehaviour : public TextInputBehaviour {
      public:
        void onChange(const std::string &value) override;
    };

}