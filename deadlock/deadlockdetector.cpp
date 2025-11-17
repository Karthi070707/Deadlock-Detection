#include "DeadlockDetector.h"
#include <iostream>

// Constructor
DeadlockDetector::DeadlockDetector(int num_processes, int num_resources)
    : processes(num_processes), resources(num_resources) {
    
    total_resources.resize(resources, 0);
    available.resize(resources, 0);
    allocation.resize(processes, std::vector<int>(resources, 0));
    request.resize(processes, std::vector<int>(resources, 0));
}

void DeadlockDetector::setTotalResources(const std::vector<int>& total_vec) {
    total_resources = total_vec;
    recalculateAvailable();
}

void DeadlockDetector::setAllocation(int process_id, const std::vector<int>& alloc_vector) {
    allocation[process_id] = alloc_vector;
    recalculateAvailable();
}

void DeadlockDetector::setRequest(int process_id, const std::vector<int>& request_vector) {
    request[process_id] = request_vector;
}

// Private helper to update 'available'
void DeadlockDetector::recalculateAvailable() {
    available = total_resources; // Start with total
    // Subtract all current allocations
    for (int i = 0; i < processes; ++i) {
        for (int j = 0; j < resources; ++j) {
            available[j] -= allocation[i][j];
        }
    }
}

// The core Deadlock Detection Algorithm
bool DeadlockDetector::detect() {
    std::vector<int> work = available;
    std::vector<bool> finish(processes, false);

    // Mark processes that aren't waiting as 'finished'
    for (int i = 0; i < processes; ++i) {
        bool is_waiting = false;
        for (int j = 0; j < resources; ++j) {
            if (request[i][j] > 0) {
                is_waiting = true;
                break;
            }
        }
        if (!is_waiting) {
            finish[i] = true;
        }
    }

    // Main detection loop
    bool found_process;
    do {
        found_process = false;
        for (int i = 0; i < processes; ++i) {
            if (finish[i] == false) {
                // Check if Request[i] <= Work
                bool can_satisfy = true;
                for (int j = 0; j < resources; ++j) {
                    if (request[i][j] > work[j]) {
                        can_satisfy = false;
                        break;
                    }
                }

                if (can_satisfy) {
                    // Pretend to free its resources
                    for (int j = 0; j < resources; ++j) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found_process = true;
                }
            }
        }
    } while (found_process);

    // Check for any process that is not finished
    bool deadlock_found = false;
    std::cout << "--- Detection Report ---\n";
    for (int i = 0; i < processes; ++i) {
        if (finish[i] == false) {
            std::cout << "Process P" << i << " is DEADLOCKED.\n";
            deadlock_found = true;
        }
    }

    if (!deadlock_found) {
        std::cout << "--> No deadlock detected. System is safe.\n";
    }
    std::cout << "------------------------\n";
    
    return deadlock_found;
}