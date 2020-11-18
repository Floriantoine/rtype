/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AskJoinHandler
*/

#include "AskJoinHandler.hpp"

#include "GameServer.hpp"
#include "Protocol.hpp"
#include "Server.hpp"
#include "handlers/AHandlerTCP.hpp"
#include "types.hpp"

#include <functional>
#include <memory>
#include <string.h>

namespace rtype::server {
    AskJoinHandler::AskJoinHandler(GameServer &owner)
        : AHandlerTCP(owner)
    { }

    void AskJoinHandler::receiveResponse(const BPC::Package &package, Network::TcpSession &client)
    {
    }

    void AskJoinHandler::receiveRequest(const BPC::Package &requestPackage, Network::TcpSession &client)
    {
        const ClientRequestBody *request = requestPackage.getBodyTo<ClientRequestBody>();
        LobbyDispatcher::Range range = this->owner_.dispatcher_->dispatch();
        ServerResponseBody response = { .port = 0 };
        std::shared_ptr<std::function<void()>> onSent = nullptr;
        bool good = false;

        for (; range.start != range.end; ++range.start) {
            if (strncasecmp(range.start->get()->id.data(), request->lobbyID, sizeof(lobby_id_t)) == 0) {
                good = !range.start->get()->isFull();
                break;
            }
        }
        if (good) {
            response.port = range.start->get()->getPort();
            onSent = std::make_shared<std::function<void()>>([&client] {
                client.getSocket().close();
            });
        }
        range.unlock();
        BPC::Package responsePackage(requestPackage, BPC::RESPONSE);
        responsePackage.setBodyFrom(&response);
        client.async_write(responsePackage, std::move(onSent));
    }
}
