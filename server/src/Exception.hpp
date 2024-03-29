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

    namespace Network {
        class IOException : virtual rtype::Exception {
          public:
            IOException(const std::string &msg);
            IOException(std::string &&msg);
            IOException(const std::string &msg, const std::string &part);
            IOException(std::string &&msg, std::string &&part);
            ~IOException() noexcept override = default;
            IOException &operator=(const IOException &) = delete;
            IOException &operator=(IOException &&) = delete;
        };
    };
}
