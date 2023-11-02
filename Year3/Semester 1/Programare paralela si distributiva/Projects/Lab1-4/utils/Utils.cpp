//
// Created by Dragos on 10/17/2023.
//

#include <memory>
#include "Utils.h"

std::mutex addBalanceMutex;
std::mutex subtractBalanceMutex;
std::mutex changeLogMutex;

std::list<std::shared_ptr<Account>> readAllAccounts(const std::string& fileName)
{
    std::list<std::shared_ptr<Account>> accounts_list;
    std::ifstream fileRead(fileName);

    if (!fileRead.is_open())
    {
        printf("File could not be read");
        return accounts_list;
    }

    int id, balance;
    while (fileRead >> id >> balance)
    {
        // Create a new shared_ptr<Account> and add it to the list
        auto account = std::make_shared<Account>();
        account->id = id;
        account->balance = balance;
        account->initialBalance = balance; // Assuming initialBalance is the same as balance
        accounts_list.push_back(account);
    }

    fileRead.close();
    return accounts_list;
}

int getRandomAmount(int balance) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, balance);
    return distribution(gen);
}

int getRandomAccountIndex(int numAccounts) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, numAccounts - 1);
    return distribution(gen);
}

void add_balance(int amount, std::shared_ptr<Account> receiver, int serial_number, int senderId)
{
    std::unique_lock<std::mutex> lock(addBalanceMutex);
    receiver->balance += amount;
    Operation receiver_operation{
            serial_number,
            senderId,
            receiver->id,
            amount
    };
    receiver->log.push_back(receiver_operation);
    addBalanceMutex.unlock();
}
void subtract_balance(int amount, std::shared_ptr<Account> sender, int serial_number, int receiverId)
{
    ///TODO: defer lock
    std::unique_lock<std::mutex> lock(subtractBalanceMutex);
    sender->balance -= amount;
    Operation sender_operation{
            serial_number,
            sender->id,
            receiverId,
            amount
    };
    sender->log.push_back(sender_operation);
    subtractBalanceMutex.unlock();
}
//void change_log(int amount, int serial_number, std::shared_ptr<Account> sender, std::shared_ptr<Account> receiver)
//{
//    std::unique_lock<std::mutex> lock(changeLogMutex);
//    Operation sender_operation{
//            serial_number,
//            sender->id,
//            receiver->id,
//            amount
//    };
//    Operation receiver_operation{
//            serial_number,
//            sender->id,
//            receiver->id,
//            amount
//    };
//
//    sender->log.push_back(sender_operation);
//    receiver->log.push_back(receiver_operation);
//
//    changeLogMutex.unlock();
//}