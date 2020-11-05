/*
** EPITECH PROJECT, 2020
** R-type
** File description:
** Exception
*/

#pragma once

#include <exception>
#include <string>

namespace rtype {
    /**
     * @brief generic exception class for the R-Type project
     */
    class Exception : public std::exception {
      public:
        Exception(const std::string &msg)
            : _msg(msg)
        {
        }

        Exception(std::string &&msg)
            : _msg(std::move(msg))
        {
        }

        virtual ~Exception() override = default;

        virtual const char *what() const noexcept override
        {
            return (_msg.c_str());
        }

      protected:
        const std::string _msg;
    };
}
