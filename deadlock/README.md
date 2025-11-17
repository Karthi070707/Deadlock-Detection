# C++ Deadlock Detection Simulator

A command-line C++ project that simulates an operating system's resource manager to detect deadlocks. This program implements the **Banker's Algorithm (Safety Algorithm)** to determine if a given system state is safe or if it has resulted in a deadlock.

---

###💡 Core Concept

This program models a system snapshot with three key matrices:
* **Allocation:** Resources currently *held* by each process.
* **Request:** Resources *needed* by each process to complete.
* **Available:** Resources currently free in the system.

The `detect` command runs the Safety Algorithm:
1.  It creates a "Work" vector, initially equal to the `Available` resources.
2.  It looks for a process whose `Request` can be satisfied by the `Work` vector.
3.  If found, it "pretends" that process completes, and adds its `Allocation` to the `Work` vector.
4.  It repeats this until no more processes can run.
5.  **If any processes are left unfinished, they are in a deadlock.**

---

## 🏗️ How to Compile

This project is built with C++ and split into three files:
* `DeadlockDetector.h` (The class interface)
* `DeadlockDetector.cpp` (The class implementation)
* `main.cpp` (The command-line driver)

You will need a C++ compiler like `g++`.

1.  Make sure all three files are in the same directory.
2.  Open your terminal in that directory.
3.  Run the following command to compile:

    ```bash
    g++ main.cpp DeadlockDetector.cpp -o detector
    ```
    (You can add `-std=c++11` if your compiler needs it).

---

## 🚀 How to Run & Example

1.  Execute the compiled program from your terminal:
    ```bash
    ./detector
    ```

2.  The program will ask you to set up the system. You will then use commands to define the system's state.

### Example: Creating a Deadlock

Here is a simple example with 2 processes and 2 resource types that will result in a deadlock.

```bash
$ ./detector
Enter number of processes: 2
Enter number of resource types: 2
Commands: total, alloc, req, detect, exit

> total 2 2
Total resources set.

> alloc 0 1 1
Allocation set for P0.

> alloc 1 1 1
Allocation set for P1.

> req 0 0 1
Request set for P0.

> req 1 1 0
Request set for P1.



> detect
--- Detection Report ---
Process P0 is DEADLOCKED.
Process P1 is DEADLOCKED.
------------------------

> exit
Exiting.