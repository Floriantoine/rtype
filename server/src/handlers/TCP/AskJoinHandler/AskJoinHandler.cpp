/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** AskJoinHandler
*/

#include "AskJoinHandler.hpp"

#include "Protocol.hpp"
#include "Server.hpp"
#include "handlers/AHandlerTCP.hpp"
#include <functional>

namespace rtype::server {
    AskJoinHandler::AskJoinHandler(LobbyDispatcher &dispatcher)
        : AHandlerTCP(dispatcher)
    { }

    void AskJoinHandler::response(const BPC::Package &package, Network::TcpSession &client)
    {
    }

    void AskJoinHandler::request(const BPC::Package &requestPackage, Network::TcpSession &client)
    {
        const ClientRequestBody *request = requestPackage.getBodyTo<ClientRequestBody>();
        LobbyDispatcher::Range range = this->dispatcher_.dispatch();
        bool good = false;

        for (; range.start != range.end; ++range.start) {
            if (range.start->get()->id == request->lobbyID) {
                good = !range.start->get()->isFull();
                break;
            }
        }
        ServerResponseBody response = { .port = 0 };
        std::function<void()> onSent = []{};
        if (good) {
            response.port = range.start->get()->getPort();
            onSent = [&client] {
                client.getSocket().close();
            };
        }
        range.unlock();
        BPC::Package responsePackage(requestPackage, BPC::RESPONSE);
        responsePackage.setBodyFrom(&response);
        client.async_write(responsePackage, onSent);
    }
}
