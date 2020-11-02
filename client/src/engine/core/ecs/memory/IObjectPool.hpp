/**
 * ObjectPool interface, mainly used to store ObjectPool of different types 
 * together
 */
class IObjectPool
{
protected:
    virtual ~IObjectPool() = default;

    public:
        virtual void *get() = 0;
        virtual void release(void *) = 0;
};
