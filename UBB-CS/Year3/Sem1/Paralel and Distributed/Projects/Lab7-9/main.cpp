#include <iostream>
#include "Utils/Callback.h"
#include "Utils/TaskSolution.h"
#include "Utils/AsyncAwaitSolution.h"

int main() {
    std::vector<std::string> urls = { "www.apache.org/", "www.wikipedia.org/" };

    ///CallbackSolution parser(urls);
    ///TaskSolution parser(urls);
    AsyncAwaitSolution parser(urls);
    parser.Run();

    WSACleanup();

    return 0;
}
