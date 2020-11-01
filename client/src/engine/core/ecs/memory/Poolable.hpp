#pragma once

template <class T>
struct Poolable
{
    public:
        bool isUsed { false };
        T object;

        Poolable()
            : object {}
        {};
        ~Poolable() = default;
};
