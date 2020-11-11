/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
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
            : msg_(msg)
        {
        }

        Exception(std::string &&msg)
            : msg_(std::move(msg))
        {
        }

        Exception(const std::string &msg, const std::string &part)
            : msg_(msg)
            , part_(part)
        {
        }

        Exception(std::string &&msg, std::string &&part)
            : msg_(std::move(msg))
            , part_(std::move(part))
        {
        }

        Exception &operator=(const Exception &) = delete;
        Exception &operator=(Exception &&) = delete;

        virtual ~Exception() noexcept override = default;

        virtual const char *where() const noexcept
        {
            return (this->part_.data());
        }

        virtual const char *what() const noexcept override
        {
            return (this->msg_.data());
        }

      protected:
        const std::string msg_;
        const std::string part_;
    };
}
