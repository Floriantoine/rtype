/*
** EPITECH PROJECT, 2020
** core
** File description:
** main
*/

#include "BinaryProtocolCommunication.hpp"

namespace BPC = BinaryProtocolComunication;

int main(void)
{
    auto cm = BPC::CommunicationManager::Get();
    std::vector<std::string> str = { "127.0.0.1", "4242" };

    auto buffer = cm.serialize(BPC::BaseType::REQUEST, BPC::Method::CREATE);
    cm.deserialize(buffer);
    return 0;
}

//      1              1        <                >   2
//---------------------------------------------------------------
//|  DEF_BYTE     |  is_serv   | ARGS START
//---------------------------------------------------------------
//       ^                              ^
//  type + method                  args
//                           contain in the socket...
