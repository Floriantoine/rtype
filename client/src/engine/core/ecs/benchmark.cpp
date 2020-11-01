#include <thread>
#include <functional>
#include <chrono>
#include <iostream>
#include <vector>

#define SIZE (100000000)

class Vec3_c
{
    public:
        double x = 1;
        double y = 1;
        double z = 1;
};

struct Vec3_s
{
    double x = 1;
    double y = 1;
    double z = 1;
};

auto benchmark(std::function<void ()> function)
{
    auto start = std::chrono::high_resolution_clock::now();
    function();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    return duration.count();
}

int main(void)
{
    auto t1 = std::thread([]() {
        std::vector<Vec3_c> vec(SIZE);
        auto duration = benchmark([&]() {
            for (const auto &it: vec) {}
        });
        std::cout << "class [" << SIZE << "]:" << duration << std::endl;
    });
    auto t2 = std::thread([]() {
        std::vector<Vec3_s> vec(SIZE);
        auto duration = benchmark([&]() {
            for (const auto &it: vec) {}
        });
        std::cout << "struct[" << SIZE << "]:" << duration << std::endl;
    });
    t1.join();
    t2.join();
    return 0;
}
