//
// Created by Dragos on 10/17/2023.
//

#include <memory>
#include "Utils.h"

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
        auto account = std::make_shared<Account>();
        account->id = id;
        account->balance = balance;
        account->initialBalance = balance;
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

void transfer(int amount, int serial_number, Account& sender, Account& receiver, std::vector<std::mutex>& accountMutexes)
{
    sender.lock();
    receiver.lock();

    if(sender.balance < amount)
        return;

    sender.balance -= amount;
    receiver.balance += amount;

    Operation sender_operation
            {
                    serial_number,
                    sender.id,
                    receiver.id,
                    amount
            };
    Operation receiver_operation
            {
                    serial_number,
                    sender.id,
                    receiver.id,
                    amount
            };

    sender.log.push_back(sender_operation);
    receiver.log.push_back(receiver_operation);

    sender.unlock();
    receiver.unlock();
}