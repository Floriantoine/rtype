/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Behaviour abstract class
*/

#pragma once

#include "engine/core/ABehaviourBase.hpp"

namespace rtype::server {

    /**
     * Behaviour abstract class
     *
     * Behaviours are entity-specific behaviours
     * Behaviours must inherit from this class to be triggered by the default 
     * systems
     */
    class ABehaviour : public ABehaviourBase {
    };

}
