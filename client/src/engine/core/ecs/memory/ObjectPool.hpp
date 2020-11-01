#pragma once

#include <iostream>
#include <cstddef>
#include <vector>

#include "Poolable.hpp"

template<class T, std::size_t chunkSize = 1024>
class ObjectPool
{
    private:
        std::vector<Poolable<T>> _poolables;

    public:
        ObjectPool() = default;
        ~ObjectPool() = default;

        T *get()
        {
            std::size_t index = 0;

            for (auto &it: _poolables) {
                if (!it.isUsed) {
                    it.isUsed = true;
                    return &it.object;
                }
                ++index;
            }
            this->grow();
            _poolables[index].isUsed = true;
            return &_poolables[index].object;
        }

        void release(T *ptr) const
        {
            constexpr std::size_t offset = offsetof(Poolable<T>, object);
            Poolable<T> *poolable = reinterpret_cast<Poolable<T> *>(ptr - offset);

            poolable->isUsed = false;
        }

    private:
        void grow()
        {
            _poolables.resize(_poolables.size() + chunkSize);
        }
};
