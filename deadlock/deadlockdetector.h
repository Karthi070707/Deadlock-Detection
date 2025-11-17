#ifndef DEADLOCKDETECTOR_H
#define DEADLOCKDETECTOR_H

#include <vector>

class DeadlockDetector {
public:
    // Constructor: Initializes the system
    DeadlockDetector(int num_processes, int num_resources);

    // Sets the total system resources
    void setTotalResources(const std::vector<int>& total_vec);

    // Sets the resources currently held by a process
    void setAllocation(int process_id, const std::vector<int>& alloc_vector);

    // Sets the resources a process is waiting for
    void setRequest(int process_id, const std::vector<int>& request_vector);

    // Runs the detection algorithm and prints the result
    bool detect();

private:
    // Helper to update the 'available' vector
    void recalculateAvailable();

    int processes;
    int resources;

    std::vector<int> total_resources;
    std::vector<int> available;
    std::vector<std::vector<int>> allocation;
    std::vector<std::vector<int>> request;
};

#endif