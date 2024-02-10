#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <future>

template<typename T>
class Future {
    T val;
    bool hasValue;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Future() : hasValue(false) {}

    void set(T v) {
        cv.notify_all();
        std::unique_lock<std::mutex> lck(mtx);
        hasValue = true;
        val = v;
    }

    T get() {
        std::unique_lock<std::mutex> lck(mtx);
        if (!hasValue) {
            cv.wait(lck);
        }
        return val;
    }
};

int main() {
    Future<int> future;
    int result;

    // Example of setting a value in the future
    std::thread([&future]() {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        future.set(42);
    }).detach();

    // Example of getting the value from the future
    result = future.get();

    std::cout << "Result from future: " << result << std::endl;

    return 0;
}
