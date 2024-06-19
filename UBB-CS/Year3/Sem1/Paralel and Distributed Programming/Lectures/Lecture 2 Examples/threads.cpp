#include <stdint.h>
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>

class TestClass
{
public:
    virtual ~TestClass() {}
    virtual void add(uint64_t iter) = 0;
    virtual uint64_t sum() const = 0;
};

class TestWrong : public TestClass
{
public:
    void add(uint64_t iter) override
    {
        for (uint64_t i = 0; i < iter; ++i)
        {
            m_sum += i;
        }
    }

    uint64_t sum() const override
    {
        return m_sum;
    }

private:
    uint64_t m_sum = 0;
};

class TestAtomic : public TestClass
{
public:
    TestAtomic()
        :m_sum(0)
    {

    }

    void add(uint64_t iter) override
    {
        for (uint64_t i = 0; i < iter; ++i)
        {
            // m_sum.fetch_add(i, std::memory_order_relaxed);
            m_sum.fetch_add(i, std::memory_order_seq_cst);
        }
    }

    uint64_t sum() const override
    {
        return m_sum;
    }

private:
    std::atomic<uint64_t> m_sum;
};

class TestMutex : public TestClass
{
public:
    void add(uint64_t iter) override
    {
        for (uint64_t i = 0; i < iter; ++i)
        {
            std::unique_lock<std::mutex> lck(m_mutex);
            m_sum += i;
        }
    }

    uint64_t sum() const override
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        return m_sum;
    }

private:
    mutable std::mutex m_mutex;
    uint64_t m_sum = 0;
};

void executeTest(TestClass& testObj, uint64_t iter, uint32_t nrThreads)
{
    std::vector<std::thread> threads;
    threads.reserve(nrThreads);

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();

    for (uint32_t i = 0; i < nrThreads; ++i)
    {
        threads.emplace_back([&testObj, iter]() {testObj.add(iter); });
    }
    for (uint32_t i = 0; i < nrThreads; ++i)
    {
        threads[i].join();
    }

    std::chrono::system_clock::time_point stopTime = std::chrono::system_clock::now();

    uint64_t expectedSum = (iter * (iter - 1) / 2) * nrThreads;
    uint64_t actualSum = testObj.sum();
    std::cout << "Sum: expected=" << expectedSum << ", actual=" << actualSum <<
        ((expectedSum == actualSum) ? " OK" : " wrong") << "\n";
    std::cout << "Real time=" <<
        std::chrono::duration_cast<std::chrono::microseconds>(stopTime-startTime).count() <<
        "us\n";
}

int main()
{
    TestAtomic test;
    executeTest(test, 1000000, 8);
}