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
#include <future>

std::future<int> produce(int a, int b) {
    return std::async(std::launch::async, [a,b]() {return a+b; });
}

int main(int argc, char** argv)
{
    std::future<int> f1 = produce(10, 15);
    std::future<int> f2 = produce(15, 20);
    int r = f1.get() + f2.get();
    printf("Result=%d\n", r);
}