#pragma once

template <class T>
class Singleton {
public:
    Singleton &operator=(const Singleton &) = delete;
    Singleton &operator=(Singleton &&) = delete;

    static T &getInstance() {
		static Instance instance;

		return instance;
    };

protected:
    Singleton() {};

private:
    struct Instance : public T {
        Instance() : T() {}
    };
};
