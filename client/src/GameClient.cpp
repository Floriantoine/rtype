/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** GameClient
*/

#include "GameClient.hpp"
#include "Exception.hpp"
#include "Protocol.hpp"
#include "types.hpp"
#include "utils/Clock.hpp"
#include "handlers/GameStateHandler/GameStateHandler.hpp"
#include "handlers/MoveHandler/MoveHandler.hpp"
#include "handlers/SpawnHandler/SpawnHandler.hpp"
#include "handlers/GrabHandler/GrabHandler.hpp"
#include "handlers/DropHandler/DropHandler.hpp"
#include "handlers/ChargeHandler/ChargeHandler.hpp"
#include "handlers/PositionHandler/PositionHandler.hpp"
#include "handlers/ShootHandler/ShootHandler.hpp"
#include "handlers/HitHandler/HitHandler.hpp"
#include "handlers/JoinHandler/JoinHandler.hpp"
#include "handlers/LeaveHandler/LeaveHandler.hpp"

#include <cstring>
#include <memory>
#include <string>
#include <string_view>

#define LOBBY_ID_SIZE 6

namespace rtype::client {
    GameClient::GameClient(const int argc, const char **argv)
        : conn_(std::make_shared<Network::UdpClient>([this](const BPC::Package &pkg) {
            this->onPacketReceived_(pkg);
        }))
        , handlers_ {
            { BPC::GAME_STATE, std::make_shared<GameStateHandler>(*this) },
            { BPC::MOVE, std::make_shared<MoveHandler>(*this) },
            { BPC::SPAWN, std::make_shared<SpawnHandler>(*this) },
            { BPC::GRAB, std::make_shared<GrabHandler>(*this) },
            { BPC::DROP, std::make_shared<DropHandler>(*this) },
            { BPC::CHARGE, std::make_shared<ChargeHandler>(*this) },
            { BPC::SHOOT, std::make_shared<PositionHandler>(*this) },
            { BPC::SHOOT, std::make_shared<ShootHandler>(*this) },
            { BPC::HIT, std::make_shared<HitHandler>(*this) },
            { BPC::JOIN, std::make_shared<JoinHandler>(*this) },
            { BPC::LEAVE, std::make_shared<LeaveHandler>(*this) }
        }
    {
        if (argc != 3 && argc != 4) {
            throw Exception(std::string(argv[0]) + " <IP> <PORT> [LOBBY_ID]");
        }
        BPC::Package package = this->getInitialPackage_(argc, argv);
        unsigned short port = atoi(argv[2]);
        port = this->connectToLobby_(argv[1], port, package);

        this->conn_->connect(std::string_view(argv[1]), port);
        this->conn_->start();
    }

    port_t GameClient::connectToLobby_(const char *ip, port_t port, const BPC::Package &package)
    {
        Network::TcpClient connection(this->io_context_, std::string_view(ip), port);

        connection.send(package);
        auto response_package = connection.recv();
        if (response_package.type != BPC::RESPONSE || response_package.bodySize != 2
            || (response_package.method != BPC::CREATE && response_package.method != BPC::ASK_JOIN))
            throw rtype::client::Exception("Lobby connection: bad response from server");
        port_t *udpPort = reinterpret_cast<port_t *>(response_package.body.data());
        return *udpPort;
    }

    BPC::Package GameClient::getInitialPackage_(const int argc, const char **argv)
    {
        BPC::Package package;
        package.type = BPC::REQUEST;
        package.method = BPC::CREATE;
        package.timestamp = Clock::Now().time_since_epoch().count();

        if (argc == 4) {
            if (std::strlen(argv[3]) != LOBBY_ID_SIZE) {
                std::string err = "Malformed LOBBY_ID: ";
                err += (int)LOBBY_ID_SIZE;
                err += " characters expected";
                throw Exception(err);
            }
            package.body.reserve(LOBBY_ID_SIZE);
            for (int i = 0; i < LOBBY_ID_SIZE; ++i)
                package.body[i] = argv[3][i];
            package.bodySize = LOBBY_ID_SIZE;
            package.method = BPC::ASK_JOIN;
        }
        return package;
    }

    void GameClient::onPacketReceived_(const BPC::Package &pkg) 
    {
        auto it = std::find_if(
            this->handlers_.cbegin(),
            this->handlers_.cend(),
            [&pkg](const auto &it) {
                return pkg.method == it.first;
            });

        if (it != this->handlers_.cend()) {
            it->second->receive(pkg);
        } else {
            AHandlerUDP::unknowPacket(pkg);
        }
    }

    void GameClient::Start(const int argc, const char **argv)
    {
        static GameClient gameClient(argc, argv);
    }
}
