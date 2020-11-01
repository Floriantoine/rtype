#pragma once

#include <cstddef>
#include <vector>
#include <numeric>
#include <stdexcept>

template<class T, std::size_t chunkSize = 1024>
class ObjectPool
{
    private:
        class Chunk
        {
            private:
                std::vector<std::size_t> unusedIds_;
                std::vector<T> objects_;

            public:
                Chunk()
                    : unusedIds_ { std::vector<std::size_t>(chunkSize) }
                    , objects_ { std::vector<T>(chunkSize) }
                {
                    std::iota(this->unusedIds_.begin(), this->unusedIds_.end(), 0);
                }

                bool isFull() const
                {
                    return this->unusedIds_.size() == 0;
                }

                T *get()
                {
                    if (isFull()) {
                        throw std::out_of_range("Cannot get object from a full chunk");
                    }
                    std::size_t id = this->unusedIds_.back();
                    this->unusedIds_.pop_back();
                    return &this->objects_[id];
                }

                void release(T *ptr)
                {
                    std::size_t index = this->getObjectId(ptr);
                    this->unusedIds_.push_back(index);
                }

                bool contains(T *ptr) const
                {
                    std::intptr_t regionStart = reinterpret_cast<std::intptr_t>(&this->objects_[0]);
                    std::intptr_t regionSize = sizeof(T) * chunkSize;
                    std::intptr_t regionEnd = regionStart + regionSize;
                    std::intptr_t objectPtr = reinterpret_cast<std::intptr_t>(ptr);
                    return (regionStart <= objectPtr && objectPtr < regionEnd);
                }

            private:
                std::size_t getObjectId(T *ptr) const
                {
                    ptrdiff_t index = ptr - &this->objects_[0];
                    return index;
                }
        };

        std::vector<Chunk> chunks_;

    public:
        ObjectPool() = default;
        ~ObjectPool() = default;

        T *get()
        {
            for (auto &chunk: this->chunks_) {
                if (!chunk.isFull()) {
                    return chunk.get();
                }
            }
            this->grow();
            return this->chunks_.back().get();
        }

        void release(T *ptr)
        {
            for (auto &chunk: this->chunks_) {
                if (chunk.contains(ptr)) {
                    chunk.release(ptr);
                    return;
                }
            }
            throw std::invalid_argument("Cannot release object from this pool");
        }

    private:
        void grow()
        {
            this->chunks_.push_back(Chunk());
        }
};
