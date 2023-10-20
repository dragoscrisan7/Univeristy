#include <list>
#include <thread>
#include <mutex>
#include <random>
#include <memory>
#include "utils/Utils.h"
#include "checks//Checks.h"

int main() {
    std::string filename = R"(C:\Users\Dragos\Facultate_no-Onedrive\Year3\Programare paralela si distributiva\Projects\Lab1\accounts.txt)"; // Replace with your file name
    std::list<std::shared_ptr<Account>> accounts = readAllAccounts(filename);

    std::vector<std::mutex> accountMutexes(accounts.size());
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

        Account& sender = *accounts.front();
        Account& receiver = *accounts.front();
        int amount = getRandomAmount(sender.balance);

        transferThreads.emplace_back(transfer, amount, i, std::ref(sender), std::ref(receiver), std::ref(accountMutexes));
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 4);
    nrChecks = distribution(gen);
    std::thread consistencyThread(periodicConsistencyCheck, std::ref(accounts), nrChecks, std::ref(accountMutexes));

    // Wait for all transfer threads to finish
    for (std::thread& t : transferThreads) {
        t.join();
    }
    consistencyThread.join();

    printAccounts(accounts);

    consistencyCheck(accounts, std::ref(accountMutexes));

    return 0;
}