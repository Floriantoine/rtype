/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateHandler
*/

#include "CreateHandler.hpp"

namespace rtype {
    CreateHandler::ClientRequestBody::ClientRequestBody(std::vector<unsigned char> buffer)
        : mapName(buffer.size() + 1, '\0')
    {
        const auto len = buffer.size();

        for (auto i = 0ul; i < len; ++i) {
            this->mapName[i] = buffer[i];
        }
    }

    void CreateHandler::response(const BPC::Package &package)
    {
    }

    void CreateHandler::request(const BPC::Package &package)
    {
    }
}
