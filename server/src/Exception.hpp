/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Exception
*/

#pragma once

#include "utils/Exception.hpp"

namespace rtype::server {
    /**
    * @brief server-side parent exception class
    */
    class Exception : public rtype::Exception {
      public:
        Exception(const std::string &msg);
        Exception(std::string &&msg);
        virtual ~Exception() override = default;
    };
}