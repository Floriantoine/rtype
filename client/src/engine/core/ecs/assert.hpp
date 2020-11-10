/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Assertion macros
*/

#pragma once

#define STATIC_ASSERT_IS_COMPONENT(T) \
    static_assert(std::is_base_of<ComponentBase, T>::value, "T must inherit from ComponentBase");
