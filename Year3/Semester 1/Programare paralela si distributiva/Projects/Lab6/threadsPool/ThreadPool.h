#ifndef LAB6_THREADPOOL_H
#define LAB6_THREADPOOL_H

#include <functional>
#include <mutex>
#include <thread>
#include <list>
#include <condition_variable>
#include "../utils/Utils.h"

class ThreadPool {
public:
    explicit ThreadPool(size_t nrThreads)
            :m_end(false){
        m_threads.reserve(nrThreads);
        for (size_t i = 0; i < nrThreads; ++i) {
            m_threads.emplace_back([this]() {this->run(); });
        }
    }

    ~ThreadPool() {
        close();
        for (std::thread& t : m_threads) {
            t.join();
        }
    }

    void close() {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_end = true;
        m_cond.notify_all();
    }

    void enqueue(std::function<void()> func) {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_queue.push_back(std::move(func));
        m_cond.notify_one();
    }
private:
    void run() {
        while (true) {
            std::function<void()> toExec;
            {
                std::unique_lock<std::mutex> lck(m_mutex);
                while (m_queue.empty() && !m_end) {
                    m_cond.wait(lck);
                }
                if (m_queue.empty()) {
                    return;
                }
                toExec = std::move(m_queue.front());
                m_queue.pop_front();
            }
            toExec();
        }
    }

    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::list<std::function<void()>> m_queue;
    bool m_end;
    std::vector<std::thread> m_threads;
};

void TPparallelMatrixProduct(const std::vector<std::vector<int>>& matrixA, const std::vector<std::vector<int>>& matrixB, std::vector<std::vector<int>>& result, int taskID, int numTasks);


#endif //LAB6_THREADPOOL_H