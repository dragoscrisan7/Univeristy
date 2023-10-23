#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::mutex mtx;
std::condition_variable cv;
bool dataReady = false;

std::vector<int> vector1 = {1, 2, 3, 4, 5};
std::vector<int> vector2 = {5, 4, 3, 2, 1};
int partialSum = 0;
int currentIndex = 0;

void producer() {
    for (size_t i = 0; i < vector1.size(); ++i) {
        int product = vector1[i] * vector2[i];

        std::unique_lock<std::mutex> lock(mtx);
        // Wait for the consumer to consume the previous product
        cv.wait(lock, [] { return !dataReady; });

        partialSum = product;
        currentIndex = i;
        dataReady = true;
        lock.unlock();
        cv.notify_one();  // Notify the consumer
    }
}

void consumer() {
    int totalSum = 0;
    for (size_t i = 0; i < vector1.size(); ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        // Wait for the producer to provide data
        cv.wait(lock, [] { return dataReady; });

        totalSum += partialSum;
        dataReady = false;
        lock.unlock();
        cv.notify_one();  // Notify the producer
    }

    std::cout << "The scalar product is: " << totalSum << std::endl;
}

int main() {
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
