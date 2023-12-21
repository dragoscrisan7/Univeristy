#ifndef LAB1_CHECKS_H
#define LAB1_CHECKS_H

#include <iostream>
#include <thread>
#include <atomic>
#include <list>
#include <vector>
#include <mutex>
#include "../utils/Utils.h" // Include the updated Utils.h


void consistencyCheck(const std::list<std::shared_ptr<Account>>& accounts);
void periodicConsistencyCheck(std::list<std::shared_ptr<Account>> accounts, int var);
void printAccounts(const std::list<std::shared_ptr<Account>>& accounts);

#endif // LAB1_CHECKS_H
