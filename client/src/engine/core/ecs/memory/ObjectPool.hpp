/*
** EPITECH PROJECT, 2020
** B-CPP-501-BDX-5-1-rtype-albert.corson
** File description:
** Object pool class
*/

#pragma once

#include <cstddef>
#include <vector>
#include <numeric>
#include <stdexcept>
#include <mutex>

#include "engine/core/ecs/types.hpp"
#include "engine/core/ecs/memory/IObjectPool.hpp"

namespace rtype
{

/**
 * ObjectPool design pattern implementation
 *
 * An ObjectPool gives access to a pre-allocated pool of objects of a given 
 * type. This pattern saves numerous memory operations which can be
 * time-consuming
 *
 * @tparam T type of the objects to hold
 * @tparam chunkSize size of a chunk (pre-allocated pool of objects)
 */
template<class T, std::size_t chunkSize = 1024>
class ObjectPool: public IObjectPool
{
    private:
        /**
         * A Chunk holds a pre-allocated set of objects of type T and ways to
         * access them
         */
        class Chunk
        {
            private:
                // List of indices of objects that are available for use
                std::vector<id_t> unusedIds_;
                // List of objects
                std::vector<T> objects_;

            public:
                /**
                 * Construct a new Chunk object
                 *
                 * @constructor
                 */
                Chunk()
                    : unusedIds_ ( chunkSize )
                    , objects_ ( chunkSize )
                {
                    std::iota(this->unusedIds_.begin(), this->unusedIds_.end(), 0);
                }
                Chunk(const Chunk &other)
                    : unusedIds_ { other.unusedIds_ }
                    , objects_ { other.objects_ }
                {}
                Chunk(Chunk &&) = delete;

                Chunk &operator=(const Chunk &) = delete;

                /**
                 * Tells whether a Chunk has available objects remaining or not
                 *
                 * @return true if the chunk is full, false otherwise
                 */
                bool isFull() const
                {
                    return this->unusedIds_.size() == 0;
                }

                /**
                 * Get an object from the Chunk if one is available
                 *
                 * @throws std::out_of_range if the chunk is full
                 *
                 * @return object from the pool
                 */
                template<typename ...Args>
                T *get(Args&&...args)
                {
                    if (isFull()) {
                        throw std::out_of_range("Cannot get object from a full chunk");
                    }
                    id_t id = this->unusedIds_.back();
                    this->unusedIds_.pop_back();
                    this->objects_[id] = T(std::forward<Args>(args)...);
                    return &this->objects_[id];
                }

                /**
                 * Tags an object as available for reuse
                 *
                 * @param ptr pointer to the object to release
                 */
                void release(T *ptr)
                {
                    id_t index = this->getObjectId(ptr);
                    this->unusedIds_.push_back(index);
                }

                /**
                 * Tells whether the given pointer is contained within the 
                 * chunk bounds
                 *
                 * @param ptr pointer to consider
                 *
                 * @return true if the pointer is contained within the chunk 
                 * bounds, false otherwise
                 */
                bool contains(T *ptr) const
                {
                    std::intptr_t regionStart = reinterpret_cast<std::intptr_t>(&this->objects_[0]);
                    std::intptr_t regionSize = sizeof(T) * chunkSize;
                    std::intptr_t regionEnd = regionStart + regionSize;
                    std::intptr_t objectPtr = reinterpret_cast<std::intptr_t>(ptr);
                    return (regionStart <= objectPtr && objectPtr < regionEnd);
                }

            private:
                /**
                 * Get an object index in the chunk from its pointer
                 *
                 * @param ptr object pointer
                 *
                 * @return object index
                 */
                id_t getObjectId(T *ptr) const
                {
                    ptrdiff_t index = ptr - &this->objects_[0];
                    return index;
                }
        };

        // List of chunks
        std::vector<Chunk> chunks_;

    public:
        ObjectPool() = default;
        ObjectPool(const ObjectPool &) = delete;
        ObjectPool(ObjectPool &&) = delete;
        ~ObjectPool() = default;

        ObjectPool &operator=(const ObjectPool &) = delete;

        /**
         * Get an object from the pool if one is available, otherwise 
         * creates one
         *
         * @return object from the pool
         */
        void *get() override
        {
            for (auto &chunk: this->chunks_) {
                if (!chunk.isFull()) {
                    return chunk.get();
                }
            }
            this->grow();
            return this->chunks_.back().get();
        }

        /**
         * Get an object from the pool if one is available, otherwise
         * creates one
         *
         * @return object from the pool
         */
        template<typename ...Args>
        void *get(Args&&... args)
        {
            for (auto &chunk: this->chunks_) {
                if (!chunk.isFull()) {
                    return chunk.get(std::forward<Args>(args)...);
                }
            }
            this->grow();
            return this->chunks_.back().get(std::forward<Args>(args)...);
        }

        /**
         * Return an object back to the pool, tagging it as unused and 
         * available for reuse
         *
         * @param ptr pointer to the object to release
         *
         * @throws std::invalid_argument if the given pointer does not belong 
         * to the pool
         */
        void release(void *ptr) override
        {
            T *typePtr = static_cast<T *>(ptr);
            for (auto &chunk: this->chunks_) {
                if (chunk.contains(typePtr)) {
                    chunk.release(typePtr);
                    return;
                }
            }
            throw std::invalid_argument("Cannot release object from this pool");
        }

    private:
        /**
         * Expand the pool storage capacity
         */
        void grow()
        {
            this->chunks_.emplace_back();
        }
};

}