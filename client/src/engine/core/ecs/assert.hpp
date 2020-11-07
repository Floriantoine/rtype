#pragma once

#define STATIC_ASSERT_IS_COMPONENT(T) \
    static_assert(std::is_base_of<ComponentBase, T>::value, "T must inherit from ComponentBase");
