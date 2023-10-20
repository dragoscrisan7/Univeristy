// Utils.h

#ifndef LAB1_UTILS_H
#define LAB1_UTILS_H

#include <list>
#include <string>
#include <fstream>
#include <random>
#include <mutex>
#include <thread>
#include <atomic>

typedef struct
{
    int serial_number;
    int accountSenderId;
    int accountReceiverId;
    int amount;
}Operation;

typedef struct Account : public std::mutex
{
    int id;
    int balance;
    int initialBalance;
    std::list<Operation> log;
}Account;

std::list<std::shared_ptr<Account>> readAllAccounts(const std::string& fileName);
int getRandomAmount(int balance);
int getRandomAccountIndex(int numAccounts);
void transfer(int amount, int serial_number, Account& sender, Account& receiver, std::vector<std::mutex>& accountMutexes);

#endif // LAB1_UTILS_H