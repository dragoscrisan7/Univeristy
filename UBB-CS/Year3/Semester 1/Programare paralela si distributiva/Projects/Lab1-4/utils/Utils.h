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

struct Account {
    int id;
    int balance;
    int initialBalance;
    std::list<Operation> log;
};

extern std::mutex addBalanceMutex;
extern std::mutex subtractBalanceMutex;
extern std::mutex changeLogMutex;

std::list<std::shared_ptr<Account>> readAllAccounts(const std::string& fileName);
int getRandomAmount(int balance);
int getRandomAccountIndex(int numAccounts);

void add_balance(int amount, std::shared_ptr<Account> sender, int serial_number, int receiverId);
void subtract_balance(int amount, std::shared_ptr<Account> receiver, int serial_number, int senderId);
void change_log(int amount, int serial_number, std::shared_ptr<Account> sender, std::shared_ptr<Account> receiver);
#endif // LAB1_UTILS_H