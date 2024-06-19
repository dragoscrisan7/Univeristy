/* This program demonstrates a simple usage of futures.
* The main program creates (via the async() call) two threads that do some computation.
*   Then, the main thread waits for their results, adds them together and prints the result.
*/

#include <stdio.h>
#include <stdint.h>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <optional>
#include <queue>
#include <memory>
#include <type_traits>

template<typename T>
class Future
{
public:
    virtual ~Future() {}
    T get() const
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_cv.wait(lck, [this]() {return m_isSet; });
        return m_val;
    }

    void set(T val)
    {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_val = val;
        m_isSet = true;
        m_cv.notify_all();
    }
private:
    bool m_isSet = false;
    T m_val;
    mutable std::mutex m_mutex;
    mutable std::condition_variable m_cv;
};

template<typename Func>
class AsyncTask : public Future<typename std::invoke_result<Func>::type>
{
public:
    explicit AsyncTask(Func f)
        :m_func(f),
        m_thread([this]() {threadFunc(); })
    {
        // nothing
    }
    ~AsyncTask() override
    {
        m_thread.join();
    }
private:
    void threadFunc() {
        this->set(m_func());
    }

    Func m_func;
    std::thread m_thread;
};


template<typename Func>
std::shared_ptr<Future<typename std::invoke_result<Func>::type> > launchAsync(Func f)
{
    return std::make_shared<AsyncTask<Func> >(f);
}

std::shared_ptr<Future<int> > produce(int a, int b) {

    return launchAsync([a, b]() {return a + b; });
}

int main(int argc, char** argv)
{
    std::shared_ptr<Future<int> > f1 = produce(10, 15);
    std::shared_ptr<Future<int> > f2 = produce(15, 20);
    int r = f1->get() + f2->get();
    printf("Result=%d\n", r);
}