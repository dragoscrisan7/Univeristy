//
// Created by Dragos on 10/17/2023.
//

#ifndef LAB1_CHECKS_H
#define LAB1_CHECKS_H

#include <iostream>
#include <thread>
#include <atomic>
#include <list>
#include <string>
#include <fstream>
#include <mutex>
#include "..\utils\Utils.h"

void consistencyCheck(const std::list<std::shared_ptr<Account>> accounts, std::vector<std::mutex>& accountMutexes);
void periodicConsistencyCheck(std::list<std::shared_ptr<Account>> accounts, int var, std::vector<std::mutex>& accountMutexes);
void printAccounts(std::list<std::shared_ptr<Account>> accounts);

#endif //LAB1_CHECKS_H