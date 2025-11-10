#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

int sumVector(const std::vector<int>& a, int start, int end) {
    int S = 0;
    for (int i = start; i < end; i++) {
        S += a[i];
    }
    return S;
}

int main() {
    const int size = 10000000;
    std::vector<int> vec(size);
    std::srand(std::time(0));
    for (int i = 0; i < size; i++) {
        vec[i] = std::rand() % 100;
    }

    auto st_single = std::chrono::high_resolution_clock::now();
    int sum_single = sumVector(vec, 0, size);
    auto end_single = std::chrono::high_resolution_clock::now();
    double time_single = std::chrono::duration<double>(end_single - st_single).count();
    std::cout << "one threaded sum: " << sum_single << std::endl;
    std::cout << "one threaded time: " << time_single << " seconds" << std::endl;

    int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
    auto st_multi = std::chrono::high_resolution_clock::now();
    std::thread t1([&sum1, &vec]() { sum1 = sumVector(vec, 0, 2500000); });
    std::thread t2([&sum2, &vec]() { sum2 = sumVector(vec, 2500000, 5000000); });
    std::thread t3([&sum3, &vec]() { sum3 = sumVector(vec, 5000000, 7500000); });
    std::thread t4([&sum4, &vec]() { sum4 = sumVector(vec, 7500000, 10000000); });
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    int sum_multi = sum1 + sum2 + sum3 + sum4;
    auto end_multi = std::chrono::high_resolution_clock::now();
    double time_multi = std::chrono::duration<double>(end_multi - st_multi).count();
    std::cout << "many threaded sum: " << sum_multi << std::endl;
    std::cout << "many threaded time: " << time_multi << " seconds" << std::endl;

    return 0;
}