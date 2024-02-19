#include stdio.h
#include stdint.h
#include atomic
#include thread
#include vector
#include mutex
#include algorithm
#include functional
#include condition_variable
#include list

class ThreadPool {
public
    explicit ThreadPool(size_t nrThreads)
        m_end(false)
    {
        m_threads.reserve(nrThreads);
        for (size_t i = 0; i  nrThreads; ++i) {
            m_threads.emplace_back([this]() {this-run(); });
        }
    }

    ~ThreadPool() {
        close();
        for (stdthread& t  m_threads) {
            t.join();
        }
    }

    void close() {
        stdunique_lockstdmutex lck(m_mutex);
        m_end = true;
        m_cond.notify_all();
    }

    void enqueue(stdfunctionvoid() func) {
        stdunique_lockstdmutex lck(m_mutex);
        m_queue.push_back(stdmove(func));
        m_cond.notify_one();
    }

        templatetypename Func, typename... Args
        void enqueue(Func func, Args&&... args) {
            stdfunctionvoid() f = [=](){func(args...);};
            enqueue(stdmove(f));
        }
private
    void run() {
        while (true) {
            stdfunctionvoid() toExec;
            {
                stdunique_lockstdmutex lck(m_mutex);
                while (m_queue.empty() && !m_end) {
                    m_cond.wait(lck);
                }
                if (m_queue.empty()) {
                    return;
                }
                toExec = stdmove(m_queue.front());
                m_queue.pop_front();
            }
            toExec();
        }
    }

    stdmutex m_mutex;
    stdcondition_variable m_cond;
    stdliststdfunctionvoid()  m_queue;
    bool m_end;
    stdvectorstdthread m_threads;
};

stdunique_ptrint[] a, b;

void func(size_t start, size_t len, size_t iterations)
{
    int const aa = a.get();
    int const const bb = b.get();
    for (size_t k = 0; k  iterations; ++k) {
        for (uint64_t i = 0; i  len; ++i) {
            aa[start + i] = bb[start + i]  bb[start + i]  int(k);
        }
    }
}

int main(int argc, char argv)
{
    long long nrTasks;
    long long lenPerThread;
    long long iterations;
    long long nrThreads;
    if (argc != 5  1 != sscanf(argv[1], %lld, &nrTasks)
         1 != sscanf(argv[2], %lld, &lenPerThread)
         1 != sscanf(argv[3], %lld, &iterations)
         1 != sscanf(argv[4], %lld, &nrThreads)) {
        fprintf(stderr, Usage vector_sum_multithread nrThreads lenPerThread iterations maxThreadsn);
        return 1;
    }

    long long totalSize = nrTasks  lenPerThread;
    a.reset(new int[totalSize]);
    b.reset(new int[totalSize]);

    ThreadPool pool(nrThreads);

    for (unsigned i = 0; i  nrTasks; ++i) {
        pool.enqueue([i, lenPerThread, iterations]() {func(lenPerThread  i, lenPerThread, iterations); });
    }
    pool.close();
}