#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>

#define N 5  

class Semaphore {
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    Semaphore(int count_ = 0) : count(count_) {}

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&](){ return count > 0; });
        --count;
    }

    void release() {
        std::unique_lock<std::mutex> lock(mtx);
        ++count;
        cv.notify_one();
    }
};

Semaphore chopstick[N] = {Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1), Semaphore(1)};

void philosopher(int id) {
    while (true) {
        std::cout << "Philosopher " << id << " is thinking...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));

        chopstick[id].acquire();

        chopstick[(id + 1) % N].acquire();

        std::cout << "Philosopher " << id << " is eating...\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));

        chopstick[id].release();
        chopstick[(id + 1) % N].release();

        std::cout << "Philosopher " << id << " finished eating and put down chopsticks.\n";
    }
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < N; ++i) {
        threads.emplace_back(philosopher, i);
    }

    for (auto& t : threads) {
        t.join();
    }

}
