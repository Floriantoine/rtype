/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** CreateHandler
*/

#include "CreateHandler.hpp"

#include "handlers/AHandlerTCP.hpp"

#include <iostream>
#include <new>

namespace rtype::server {
    CreateHandler::ClientRequestBody::ClientRequestBody(const std::vector<unsigned char> &buffer)
        : mapName(buffer.size() + 1, '\0')
    {
        const auto len = buffer.size();

        for (auto i = 0ul; i < len; ++i) {
            this->mapName[i] = buffer[i];
        }
    }

    CreateHandler::CreateHandler(LobbyDispatcher &dispatcher)
        : AHandlerTCP(dispatcher)
    { }

    void CreateHandler::response(const BPC::Package &package, Network::TcpSession &client)
    {
    }

    void CreateHandler::request(const BPC::Package &requestPackage, Network::TcpSession &client)
    {
        const ClientRequestBody request(requestPackage.body);
        ServerResponseBody responseBody = { 0 };
        std::function<void()> onSent = [] {};
        BPC::Package responsePackage(requestPackage, BPC::RESPONSE);

        try {
            // TODO: load scene
            const Lobby &lobby = this->dispatcher_.createLobby(/*scene*/);
            responseBody.port = lobby.getPort();
            responsePackage.setBodyFrom(&responseBody);
            onSent = [&client] {
                client.getSocket().close();
            };
        } catch (const std::bad_alloc &_) {
        }
        client.async_write(responsePackage, onSent);
    }
}
