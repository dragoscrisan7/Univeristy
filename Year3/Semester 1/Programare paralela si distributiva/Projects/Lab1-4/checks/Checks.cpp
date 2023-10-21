//
// Created by Dragos on 10/17/2023.
//

#include <memory>
#include "Checks.h"

void consistencyCheck(const std::list<std::shared_ptr<Account>>& accounts) {
    for (const std::shared_ptr<Account>& account : accounts) {
        if (account->log.empty() && account->balance == account->initialBalance)
            return;

        // Iterate through the account's log and verify operations
        int currentBalance = account->initialBalance;
        for (const Operation& op : account->log) {
            if (op.accountSenderId == account->id) {
                currentBalance -= op.amount;
            } else if (op.accountReceiverId == account->id) {
                currentBalance += op.amount;
            }
        }
        if (currentBalance != account->balance) {
            std::cout << "Account ID: " << account->id << " has inconsistencies in its log." << std::endl;
            break;
        }
    }
}

void periodicConsistencyCheck(std::list<std::shared_ptr<Account>> accounts, int var) {
    for (int i = 0; i <= var; i++) {
        // Sleep for a specified interval (e.g., 10 seconds)
        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Perform consistency checks
        consistencyCheck(accounts);
    }
}

void printAccounts(const std::list<std::shared_ptr<Account>>& accounts)
{
    for (const std::shared_ptr<Account>& account : accounts) {
        std::cout << "ID: " << account->id << " Balance: " << account->balance << std::endl;
        for (const Operation& operation : account->log){
            std::cout << "ID: " << operation.serial_number << " accountSenderId: " << operation.accountSenderId
                      << " accountReceiverId: " << operation.accountReceiverId
                      << " amount: " << operation.amount << std::endl;
        }
    }
}