#include <list>
#include <thread>
#include <mutex>
#include <memory>
#include "utils/Utils.h"
#include "checks//Checks.h"

std::mutex mtx;

int main() {
    std::string filename = R"(C:\Users\Dragos\Facultate_no-Onedrive\UniveristyGithub\Year3\Semester 1\Programare paralela si distributiva\Projects\Lab1-4\accounts.txt)";
    std::list<std::shared_ptr<Account>> accounts = readAllAccounts(filename);

    int nrChecks;

    printAccounts(accounts);

    std::list<std::thread> transferThreads;
    int numTransactions = 30;

    for (int i = 0; i < numTransactions; ++i) {
        int senderIdx, receiverIdx;
        do {
            senderIdx = getRandomAccountIndex(accounts.size());
            receiverIdx = getRandomAccountIndex(accounts.size());
        } while (senderIdx == receiverIdx);

        std::shared_ptr<Account> sender = *std::next(accounts.begin(), senderIdx);
        std::shared_ptr<Account> receiver = *std::next(accounts.begin(), receiverIdx);

        int amount = getRandomAmount(sender->balance);

        std::unique_lock<std::mutex> lock(mtx);

        add_balance(amount, receiver);

        subtract_balance(amount, sender);

        change_log(amount, i, sender, receiver);

        // Release the mutex
        lock.unlock();

    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 4);
    nrChecks = distribution(gen);
    std::thread consistencyThread(periodicConsistencyCheck, std::ref(accounts), std::ref(nrChecks));

    // Wait for all transfer threads to finish
    for (std::thread& t : transferThreads) {
        t.join();
    }
    consistencyThread.join();

    printAccounts(accounts);

    consistencyCheck(accounts);

    return 0;
}