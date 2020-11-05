/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Lobby
*/

#pragma once

namespace rtype::server {
    /**
    * @brief representation of a lobby, where the game logic is processed
    */
    class Lobby {
      private:
        bool isRunning_ { true };

      public:
        Lobby() = default;
        ~Lobby() = default;

        /**
        * @brief processes the game logic
        */
        void onTick();

        /**
        * @return true the lobby is running
        * @return false the lobby has closed
        */
        bool isRunning() const noexcept;
    };
}