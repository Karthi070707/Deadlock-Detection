#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "DeadlockDetector.h" // Include your class

int main() {
    int num_p, num_r;
    std::cout << "Enter number of processes: ";
    std::cin >> num_p;
    std::cout << "Enter number of resource types: ";
    std::cin >> num_r;

    DeadlockDetector detector(num_p, num_r);

    std::cout << "Commands: total, alloc, req, detect, exit\n";

    std::string line;
    std::cin.ignore(); // Clear the newline buffer

    // Command loop
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "exit") {
            break;
        } else if (command == "detect") {
            detector.detect();
        } else if (command == "total") {
            std::vector<int> vec(num_r);
            for (int i = 0; i < num_r; ++i) ss >> vec[i];
            detector.setTotalResources(vec);
            std::cout << "Total resources set.\n";
        } else if (command == "alloc" || command == "req") {
            int pid;
            ss >> pid;
            std::vector<int> vec(num_r);
            for (int i = 0; i < num_r; ++i) ss >> vec[i];

            if (command == "alloc") {
                detector.setAllocation(pid, vec);
                std::cout << "Allocation set for P" << pid << ".\n";
            } else {
                detector.setRequest(pid, vec);
                std::cout << "Request set for P" << pid << ".\n";
            }
        } else {
            std::cout << "Error: Unknown command.\n";
        }
    }

    std::cout << "Exiting.\n";
    return 0;
}