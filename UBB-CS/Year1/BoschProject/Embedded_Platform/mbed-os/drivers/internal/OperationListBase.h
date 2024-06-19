/*
 * Copyright (c) 2018-2019, Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MBED_OPERATION_LIST_BASE_H
#define MBED_OPERATION_LIST_BASE_H

#include "drivers/internal/LinkedListBase.h"

class AsyncOp;

/**
 * \defgroup drivers_OperationListBase OperationListBase class
 * \ingroup drivers-internal-api-usb
 * @{
 */
class OperationListBase {
public:

    /**
     * Create a new empty operation list
     */
    OperationListBase();

    /**
     * Destroy this object and abort all operations
     */
    ~OperationListBase();

    /**
     * Check if the list is empty
     *
     * @return true if the list is empty false otherwise
     */
    bool empty();

    /**
     * Add an operation to the list
     *
     * If the list was empty then call process on this
     * operation
     *
     * @param op Operation to add
     */
    void add(AsyncOp *op);

    /**
     * Remove an operation from the list
     *
     * If this was the head of the list then process the
     * next element in the list.
     *
     * @param op Operation to remove
     */
    void remove(AsyncOp *op);

    /**
     * Dequeue the head of the list
     *
     * Remove the head of the operation list without completing it
     * or processing the next element. The caller must call the
     * AsnycOp::complete() function of the returned object.
     * Additionally process() must be called on this object
     * if there are still elements in the list.
     *
     * @return The asynchronous op at the head of the list
     */
    AsyncOp *dequeue_raw();

    /**
     * Abort all operations
     */
    void remove_all();

    /**
     * Process the operation list
     *
     * This allow the operation at the head of the list to perform processing
     */
    void process();

private:
    friend class AsyncOp;

    LinkedListBase _list;
};

/** @}*/

#endif
