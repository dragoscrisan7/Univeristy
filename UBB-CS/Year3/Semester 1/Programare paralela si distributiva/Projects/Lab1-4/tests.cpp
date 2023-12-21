#include <iostream>
#include <list>
#include <vector>
#include <thread>
#include <mutex>
#include <cassert>
#include "checks/Checks.h"

int main() {
    // Load test accounts
    std::string testFilename = R"(C:\Users\Dragos\Facultate_no-Onedrive\Year3\Programare paralela si distributiva\Projects\Lab1\accounts.txt)";
    std::list<Account> testAccounts = readAllAccounts(testFilename);

    // Create test accountMutexes
    std::vector<std::mutex> testAccountMutexes(testAccounts.size());

    // Test transfer function
    Account& sender = testAccounts.front(); // Assume the first account is the sender
    Account& receiver = testAccounts.back(); // Assume the last account is the receiver

    int initialSenderBalance = sender.balance;
    int initialReceiverBalance = receiver.balance;

    // Perform a test transfer
    int testAmount = 100;
    transfer(testAmount, 1, sender, receiver, testAccountMutexes);

    assert(sender.balance == initialSenderBalance - testAmount);
    assert(receiver.balance == initialReceiverBalance + testAmount);

    // Test consistency check
    consistencyCheck(testAccounts); // This should not produce any output or assert failures

    // Output the test results
    std::cout << "All tests passed." << std::endl;

    return 0;
}